/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:04:30 by nroth             #+#    #+#             */
/*   Updated: 2023/03/02 16:09:13 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_STRUCTS_H
# define MAP_STRUCTS_H

//is_last is used for 2 things = mark a 'NULL' at the end of collecties arr in game map, 
// and to check if the exit is active, eg all collectibles have been collected.
// is_last == FALSE = exit inactive; is_last == TRUE = hooray
typedef struct s_pos
{
	int	x;
	int	y;
	int	is_last;
}	t_pos;

//shitload of freeing to do
typedef struct s_map
{
	char	**map_arr;
	char	*map_path;
	int		map_y;
	int		map_x;
	t_pos	exit_pos;
	t_pos	player_pos;
	t_pos	*collectibles;
	int		collectibles_num;
}	t_map;

#endif