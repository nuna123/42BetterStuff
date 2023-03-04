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

#ifndef VARS_AND_DEFINS_H
# define VARS_AND_DEFINS_H

# define OK					0
# define ERR				1

# define FALSE				0
# define TRUE				1

# define IMG_SIZE			32

# define MAP_ALLOWED_CHARS	"01CEP"

# define WALL				'1'
# define EMPTY				'0'
# define COLLECT			'C'
# define EXIT				'E'
# define PLAYER				'P'

# define KEY_LEFT			97
# define KEY_DOWN			115
# define KEY_RIGHT			100
# define KEY_UP				119
# define KEY_ESC			65307

# define PLAYER_IMG_PATH	"./imgs/rock.xpm"
# define WALL_IMG_PATH		"./imgs/wall.xpm"
# define EXIT_IMG_PATH		"./imgs/exit.xpm"
# define COLLECT_IMG_PATH	"./imgs/collectible.xpm"


#endif