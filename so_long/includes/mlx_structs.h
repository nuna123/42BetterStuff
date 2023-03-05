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

#ifndef MLX_STRUCTS_H
# define MLX_STRUCTS_H

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
	struct s_img	*next_img;
}	t_img;

typedef struct s_imgs
{
	t_img	*player;
	t_img	*wall;
	t_img	*collect;
	t_img	*exit;
}	t_imgs;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	*map;
	t_imgs	*imgs;
	int		height;
	int		width;
	int		moves;
}		t_game;

#endif