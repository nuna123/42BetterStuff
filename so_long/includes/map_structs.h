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

typedef struct s_pos
{
	int	x;
	int	y;
	int	is_last;
}	t_pos;

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
