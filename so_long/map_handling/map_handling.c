/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:11 by nroth             #+#    #+#             */
/*   Updated: 2023/03/06 12:29:10 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_handling.h"

/* 
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
	ft_printf("  map_x: {%i} map_y: {%i}\n", map->map_x, map->map_y);
	ft_printf("  EXIT: {%i , %i}\n", map->exit_pos.x, map->exit_pos.y);
	ft_printf("  PLAYER: {%i , %i}\n", map->player_pos.x, map->player_pos.y);
	ft_printf("  COLLECTIBLES: %i\n", map->collect_num);
	ft_printf("\n--------------------\n");
}
 */

void	fill_map_arr(char *map_path, t_map *map)
{
	char	*line;
	int		i;
	int		j;
	int		fd;

	fd = open(map_path, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	if (line)
		map->map_arr = ft_calloc(map->map_y + 1, sizeof(char *));
	while (line)
	{
		j = -1;
		while (line[++j])
		{
			if (line[j] == PLAYER)
				line[j] = EMPTY;
		}
		map->map_arr[i] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
}

t_map	*map_fill(char *map_path)
{
	int		map_fd;
	char	*line;
	t_map	*map;

	map = map_bzero();
	map->collect_num = count_char(map_path, COLLECT);
	map->map_y = count_lines(map_path);
	map->exit_pos = get_char_pos(map_path, EXIT);
	map->player_pos = get_char_pos(map_path, PLAYER);
	fill_map_arr(map_path, map);
	map_fd = open(map_path, O_RDONLY);
	line = get_next_line(map_fd);
	map->map_x = (int) ft_strlen(line) - 1;
	while (line)
	{
		free(line);
		line = get_next_line(map_fd);
	}
	close(map_fd);
	return (map);
}

void	*free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->map_y)
		free(map->map_arr[i++]);
	free(map->map_arr);
	free(map);
	return (NULL);
}

t_map	*process_map(char *map_path)
{
	t_map	*map;

	if (check_map_validity(map_path) != OK)
		return (NULL);
	map = map_fill(map_path);
	if (flood_fill(map) == ERR)
		return (free_map(map));
	return (map);
}

/* 
int	main(int argc, char **argv)
{
	char	*map_path;
	t_map	*map;

	if (argc == 2)
		map_path = argv[1];
	else if (argc == 1)
		map_path = "../maps/map.ber";
	else
		exit(1);
	map = process_map(map_path);
	if (!map)
	{
		ft_printf ("MAP NOT OK:(\n\n");
		return (1);
	}
	ft_printf ("MAP OK!\n\n");
	//print_map(map);
	free_map (map);
	return (0);
}
 */