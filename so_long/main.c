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

int flood_check_vals(int *c_e_s, t_map *map, int row, int col)
{
	if (row < 0 || col < 0 || row >= map->map_y || col >= map->map_x)
		return;
	if (map->map_arr[row][col] == EXIT)
		c_e_s[1]++;
	if (map->map_arr[row][col] == START)
		c_e_s[2]++;
	if (map->map_arr[row][col] == COLLECT)
		c_e_s[0]++;

	f_fill(c_e_s, map, row - 1, col);
	f_fill(c_e_s, map, row + 1, col);
	f_fill(c_e_s, map, row, col - 1);
	f_fill(c_e_s, map, row, col + 1);
}

void  flood_fill(char **tab, t_point size, t_point begin)
{
    char target = tab[begin.y][begin.x];
    f_fill(tab, size, target, begin.y, begin.x);
}

int	close_and_err(int fd)
{
	close (fd);
	return (ERR);
}

int	is_all_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (c != s[i])
		{
			free (s);
			return (ERR);
		}
		i++;
	}
	free (s);
	return (OK);
}

int	check_line_validity(char *map_line, int x)
{
	int	i;

	i = 0;
	if (ft_strlen(map_line) - 1 != x)
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
			return (is_all_char(map_line, WALL));
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
	if (map_fd < 0)
		return (ERR);
	map_line = get_next_line(map_fd);
	x = ft_strlen(map_line) - 1;
	if (!map_line || is_all_char(map_line, WALL) == ERR)
		return (close_and_err(map_fd));
	map_line = get_next_line(map_fd);
	while (map_line)
	{
		if (!ft_strchr(map_line, '\n'))
		{
			close (map_fd);
			return (is_all_char(map_line, WALL));
		}
		stat += check_line_validity (map_line, x);
		map_line = get_next_line(map_fd);
	}
	close(map_fd);
	return (stat);
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

int	count_char(char *path_to_file, char c)
{
	char	*line;
	int		char_count;
	int		fd;
	int		i;

	fd = open(path_to_file, O_RDONLY);
	if (fd < 0)
		return (fd);
	char_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (i < ft_strlen(line))
		{
			if (ft_strchr(&line[i], c))
			{
				i += (ft_strchr(&line[i], c) - &line[i]) + 1;
				char_count++;
			}
			else
				i = ft_strlen(line);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (char_count);
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
	close(fd);
	return (lc);
}

t_pos	*get_collectibles(char *map_path, int collectibles_num)
{
	t_pos	*collectibles;
	int		fd;
	char	*line;
	int		y;
	int		x;
	int		collect_count;

	collectibles = ft_calloc(collectibles_num + 1, sizeof (t_pos));
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	collect_count = 0;
	line = get_next_line(fd);
	y = 0;
	while (line && collect_count <= collectibles_num)
	{
		x = 0;
		while (x < ft_strlen(line))
		{
			if (ft_strchr(&line[x], COLLECT))
			{
				x += (ft_strchr(&line[x], COLLECT) - &line[x]) + 1;
				collectibles[collect_count].x = x - 1;
				collectibles[collect_count].y = y;
				collectibles[collect_count++].is_last = FALSE;
			}
			else
				x = ft_strlen(line);
		}
		free(line);
		line = get_next_line(fd);
		y++;
	}
	collectibles[collectibles_num].is_last = TRUE;
	close(fd);
	return (collectibles);
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
		ft_printf("[%i, %i] ", map->collectibles[i - 1].x, map->collectibles[i - 1].y);
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
		ft_printf("{%s}\n", line);
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
	int		x;
	int		y;

	map = map_bzero();
	map->collectibles_num	= count_char(map_path, COLLECT);
	map->collectibles		= get_collectibles(map_path,map->collectibles_num);
	map->map_y				= count_lines(map_path);
	map->exit				= get_char_pos(map_path, EXIT);
	map->start_pos			= get_char_pos(map_path, START);
	map->map_path			= ft_strdup(map_path);
	fill_map_arr(map);

	map_fd = open(map_path, O_RDONLY);
	line = get_next_line(map_fd);
	map->map_x				= ft_strlen(line - 1);
	close(map_fd);

	print_map(map);
	return (map);
}

t_map	*init_map(char *map_path)
{
	t_map	*map;
	int		map_fd;
	
	map = map_bzero();
	if (!map)
		return (NULL);
	map_fill(map_path);
	

	return (map);
}

t_map	*process_map(char *map_path)
{
	int		stat;
	t_map	*map;

	if (check_map_validity(map_path) == OK)
		map = init_map(map_path);

	return (NULL);
}

int main(int argc, char **argv)
{
	char	*map_path;

	if (argc == 2)
		map_path = argv[1];
	else if (argc == 1)
		map_path = "./maps/map.ber";
	else
		exit(1);
	
	process_map(map_path);

	return (0);
}