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
	int		collect_num;
}	t_map;

#endif