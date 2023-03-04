/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:11 by nroth             #+#    #+#             */
/*   Updated: 2023/03/02 16:53:24 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_handling.h"

// c = collectibles, val 100
// e = exit, val 1
// s = start, val 1

void	f_fill(char **tab, int *c_e_s, t_map *map, t_pos pos)
{
	if (pos.y < 0 || pos.x < 0 || pos.y >= map->map_y
		|| pos.x >= map->map_x || tab[pos.y][pos.x] == WALL)
		return ;
	else if (map->map_arr[pos.y][pos.x] == EXIT)
		*c_e_s += 1;
	else if (map->map_arr[pos.y][pos.x] == COLLECT)
		*c_e_s += 100;
	else if (pos.y == map->player_pos.y && pos.x == map->player_pos.x)
		*c_e_s += 1000;

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
	f_fill(tab, &c_e_s, map, (t_pos){map->exit_pos.x, map->exit_pos.y, TRUE});
	i--;
	while (i > -1)
		free(tab[i--]);
	free (tab);
	if (c_e_s > 1000 && (c_e_s - 1000) / 100 == map->collect_num
			&& (c_e_s - 1000) % 100 == 1)
		return (OK);
	return (ERR);
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
		if (ft_strchr(map_line, EXIT) || ft_strchr(map_line, PLAYER))
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
