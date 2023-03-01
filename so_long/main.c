/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:11 by nroth             #+#    #+#             */
/*   Updated: 2023/02/28 16:07:50 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//void f_fill(char **tab, t_point size, char target, int row, int col)
// c = collectibles, val 100
// e = exit, val 1
// s = start, val 1

void	f_fill(char **tab, int *c_e_s, t_map *map, t_pos pos)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= map->map_y
		|| pos.x >= map->map_x || tab[pos.y][pos.x] == WALL)
		return ;
	if (map->map_arr[pos.y][pos.x] == EXIT)
		*c_e_s += 1;
	if (map->map_arr[pos.y][pos.x] == START)
		*c_e_s += 1;
	if (map->map_arr[pos.y][pos.x] == COLLECT)
		*c_e_s += 100;
	tab[pos.y][pos.x] = WALL;
	f_fill(tab, c_e_s, map, (t_pos){pos.x, pos.y - 1, TRUE});
	f_fill(tab, c_e_s, map, (t_pos){pos.x, pos.y + 1, TRUE});
	f_fill(tab, c_e_s, map, (t_pos){pos.x - 1, pos.y, TRUE});
	f_fill(tab, c_e_s, map, (t_pos){pos.x + 1, pos.y, TRUE});
}

int	flood_fill(t_map *map)
{
	int		c_e_s;
	char	**tab;
	int		i;

	i = 0;
	tab = ft_calloc(map->map_y + 1, sizeof(char *));
	while (i < map->map_y)
	{
		tab[i] = ft_strdup(map->map_arr[i]);
		i++;
	}
	c_e_s = 0;
	f_fill(tab, &c_e_s, map, (t_pos){map->exit.x, map->exit.y, TRUE});
	i--;
	while (i > -1)
		free(tab[i--]);
	free (tab);
	if (c_e_s / 100 == map->collectibles_num && c_e_s % 100 == 2)
		return (OK);
	return (ERR);
}

int	close_and_return(int fd, int ret_val)
{
	close (fd);
	return (ret_val);
}

int	is_all_char(char *s, char c, void (*f)(void *arg))
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (c != s[i])
		{
			if (f)
				free (s);
			return (ERR);
		}
		i++;
	}
	if (f)
		f(s);
	return (OK);
}

int	check_line_validity(char *map_line, int x)
{
	int		i;
	char	*trimmed_line;

	i = 0;
	trimmed_line = ft_strtrim(map_line, "\n");
	free(map_line);
	map_line = trimmed_line;
	if ((int) ft_strlen(map_line) != x)
	{
		free (map_line);
		return (ERR);
	}
	while (map_line[i] && map_line[i] != '\n')
	{
		if (!ft_strchr(MAP_ALLOWED_CHARS, map_line[i])
			|| map_line[0] != WALL
			|| map_line[ft_strlen(map_line) - 1] != WALL)
		{
			free (map_line);
			return (ERR);
		}
		i++;
	}
	free (map_line);
	return (OK);
}

int	check_map_components(char *map_path)
{
	int		map_fd;
	char	*map_line;
	int		exit_start;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd < 0)
		return (ERR);
	map_line = get_next_line(map_fd);
	exit_start = 0;
	while (map_line)
	{
		if (ft_strchr(map_line, EXIT) || ft_strchr(map_line, START))
			exit_start++;
		if (ft_strchr(map_line, COLLECT))
			exit_start += 100;
		if (!ft_strchr(map_line, '\n'))
		{
			close (map_fd);
			if (exit_start <= 100 || exit_start % 100 != 2)
				return (ERR);
			return (is_all_char(map_line, WALL, free));
		}
		map_line = get_next_line(map_fd);
	}
	return (ERR);
}

int	check_map_validity(char *map_path)
{
	char	*map_line;
	int		x;
	int		map_fd;
	int		stat;

	stat = 0;
	map_fd = open(map_path, O_RDONLY);
	map_line = get_next_line(map_fd);
	x = ft_strlen(map_line) - 1;
	if (!map_line || is_all_char(map_line, WALL, free) == ERR)
		return (close_and_return(map_fd, ERR));
	map_line = get_next_line(map_fd);
	while (map_line)
	{
		if (!ft_strchr(map_line, '\n'))
		{
			close (map_fd);
			return (is_all_char(map_line, WALL, NULL)
				+ check_line_validity(map_line, x) + stat);
		}
		stat += check_line_validity (map_line, x);
		map_line = get_next_line(map_fd);
	}
	return (close_and_return(map_fd, stat));
}

t_map	*map_bzero(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->map_arr = NULL;
	map->map_y = 0;
	map->map_x = 0;
	map->collectibles_num = 0;
	map->exit.x = 0;
	map->exit.y = 0;
	map->exit.is_last = TRUE;
	map->start_pos.x = 0;
	map->start_pos.y = 0;
	map->start_pos.is_last = TRUE;
	map->collectibles = NULL;
	map->collectibles_num = 0;
	return (map);
}

void	free_arr(char **arr, int arr_size)
{
	int	i;

	if (!arr_size)
		arr_size = INT_MAX;
	i = 0;
	while (i < arr_size && arr[i])
		free(arr[i++]);
	free(arr);
}

int	arr_len(char **arr)
{
	int	cnt;

	if (!arr)
		return (0);
	cnt = 0;
	while (arr[cnt])
		cnt++;
	return (cnt);
}

int	count_char(char *path_to_file, char c)
{
	char	*line;
	char	**line_arr;
	int		char_count;
	int		fd;

	fd = open(path_to_file, O_RDONLY);
	char_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_arr = ft_split(line, c);
		char_count += arr_len(line_arr) - 1;
		free_arr (line_arr, 0);
		free(line);
		line = get_next_line(fd);
	}
	return (close_and_return(fd, char_count));
}

int	count_lines(char *path)
{
	char	*line;
	int		lc;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (fd);
	lc = 0;
	line = get_next_line(fd);
	while (line)
	{
		lc++;
		free(line);
		line = get_next_line(fd);
	}
	return (close_and_return(fd, lc));
}

int	collecties_expand(char *line, t_pos *x_y, t_pos *collecties)
{
	if (ft_strchr(&line[x_y->x], COLLECT))
	{
		x_y->x += (ft_strchr(&line[x_y->x], COLLECT) - &line[x_y->x]) + 1;
		*collecties = (t_pos){x_y->x - 1, x_y->y, FALSE};
		return (1);
	}
	else
		x_y->x = ft_strlen(line);
	return (0);
}

t_pos	*get_collectibles(char *map_path, int collectibles_num)
{
	t_pos	*collecties;
	int		fd;
	char	*line;
	t_pos	x_y;
	int		clct_cnt;

	collecties = ft_calloc(collectibles_num + 1, sizeof (t_pos));
	fd = open(map_path, O_RDONLY);
	clct_cnt = 0;
	line = get_next_line(fd);
	x_y = (t_pos){0, 0, 0};
	while (line && clct_cnt <= collectibles_num)
	{
		x_y.x = 0;
		while (x_y.x < (int) ft_strlen(line))
			clct_cnt += collecties_expand(line, &x_y, &collecties[clct_cnt]);
		free(line);
		line = get_next_line(fd);
		x_y.y++;
	}
	collecties[collectibles_num].is_last = TRUE;
	close(fd);
	return (collecties);
}

void	print_map(t_map *map)
{
	int	i;

	ft_printf("--------MAP:--------\n");
	i = 0;
	while (map->map_arr[i])
	{
		ft_printf("\t%s\n", map->map_arr[i]);
		i++;
	}
	ft_printf("  MAP_PATH: %s\n", map->map_path);
	ft_printf("  map_x: {%i} map_y: {%i}\n", map->map_x, map->map_y);
	ft_printf("  EXIT: {%i , %i}\n", map->exit.x, map->exit.y);
	ft_printf("  START: {%i , %i}\n", map->start_pos.x, map->start_pos.y);
	ft_printf("  COLLECTIBLES: num: %i\n", map->collectibles_num);
	ft_printf("    ");
	i = 1;
	while (map->collectibles[i - 1].is_last != TRUE)
	{
		ft_printf("[%i, %i] ", map->collectibles[i - 1].x,
			map->collectibles[i - 1].y);
		if (i % 3 == 0 && i != 0)
			ft_printf("\n    ");
		i++;
	}
	ft_printf("\n--------------------\n");
}

t_pos	get_char_pos(char *path_to_file, char c)
{
	char	*line;
	t_pos	pos;
	int		fd;
	int		found;

	fd = open(path_to_file, O_RDONLY);
	line = get_next_line(fd);
	found = 0;
	pos.y = 0;
	while (line)
	{
		if (ft_strchr(line, c) && !found)
		{
			pos.x = (ft_strchr(line, c) - line);
			found = 1;
		}
		free(line);
		line = get_next_line(fd);
		if (!found)
			pos.y++;
	}
	close(fd);
	return (pos);
}

void	fill_map_arr(t_map *map)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(map->map_path, O_RDONLY);
	map->map_arr = ft_calloc(map->map_y + 1, sizeof(char *));
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->map_arr[i] = ft_strtrim(line, "\t\n ");
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

t_map	*map_fill(char *map_path)
{
	int		map_fd;
	char	*line;
	t_map	*map;

	map = map_bzero();
	map->collectibles_num = count_char(map_path, COLLECT);
	map->collectibles = get_collectibles(map_path, map->collectibles_num);
	map->map_y = count_lines(map_path);
	map->exit = get_char_pos(map_path, EXIT);
	map->start_pos = get_char_pos(map_path, START);
	map->map_path = ft_strdup(map_path);
	fill_map_arr(map);
	map_fd = open(map_path, O_RDONLY);
	line = get_next_line(map_fd);
	map->map_x = (int) ft_strlen(line) - 1;
	close(map_fd);
	free(line);
	return (map);
}

void	*free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->map_y)
		free(map->map_arr[i++]);
	free(map->map_arr);
	free(map->map_path);
	free(map->collectibles);
	free(map);
	return (NULL);
}

t_map	*init_map(char *map_path)
{
	t_map	*map;

	map = map_fill(map_path);
	if (flood_fill(map) == ERR)
		return (free_map(map));
	return (map);
}

t_map	*process_map(char *map_path)
{
	t_map	*map;

	if (check_map_validity(map_path) == OK)
		map = init_map(map_path);
	return (map);
}

int	main(int argc, char **argv)
{
	char	*map_path;
	t_map	*map;

	if (argc == 2)
		map_path = argv[1];
	else if (argc == 1)
		map_path = "./maps/map.ber";
	else
		exit(1);
	map = process_map(map_path);
	if (!map)
	{
		ft_printf ("MAP NOT OK:(\n\n");
		return (1);
	}
	ft_printf ("MAP OK!\n\n");
	print_map(map);
	free_map (map);
	return (0);
}
