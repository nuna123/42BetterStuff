/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:11 by nroth             #+#    #+#             */
/*   Updated: 2023/03/02 17:00:49 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_handling.h"

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
	ft_printf("  EXIT: {%i , %i}\n", map->exit_pos.x, map->exit_pos.y);
	ft_printf("  PLAYER: {%i , %i}\n", map->player_pos.x, map->player_pos.y);
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
	map->exit_pos = get_char_pos(map_path, EXIT);
	map->player_pos = get_char_pos(map_path, PLAYER);
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

t_map	*process_map(char *map_path)
{
	t_map	*map;

	if (check_map_validity(map_path) == ERR)
		return (NULL);
	map = map_fill(map_path);
	if (flood_fill(map) == ERR)
		return (free_map(map));
	return (map);
}

int	map_handling(char *map_path)
{
	t_map	*map;

	if (!map_path)
		map_path = "./maps/map.ber";
	map = process_map(map_path);
	if (!map)
	{
		ft_printf ("MAP NOT OK:(\n\n");
		return (ERR);
	}
	ft_printf ("MAP OK!\n\n");
	print_map(map);
	free_map (map);
	return (OK);
}

/* 
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
 */