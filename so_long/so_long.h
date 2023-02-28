/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:11 by nroth             #+#    #+#             */
/*   Updated: 2023/02/28 15:34:31 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

# include "Libft/libft.h"

# define OK			0
# define ERR		1

# define FALSE		0
# define TRUE		1

# define MAP_ALLOWED_CHARS	"01CEP"

# define WALL		'1'
# define EMPTY		'0'
# define COLLECT	'C'
# define EXIT		'E'
# define START		'P'

typedef struct	s_pos
{
	int	x;
	int	y;
	int	is_last;
} t_pos;

typedef struct	s_map
{
	char	**map_arr;
	char	*map_path;
	int		map_y;
	int		map_x;
	t_pos	exit;
	t_pos	start_pos;
	t_pos	*collectibles;
	int		collectibles_num;
} t_map;

#endif