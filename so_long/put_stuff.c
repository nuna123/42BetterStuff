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

#include "so_long.h"

void	put_img(t_game *game, void *img_ptr, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		img_ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	put_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	while (++y < game->map->map_y)
	{
		x = -1;
		while (++x < game->map->map_x)
		{
			if (game->map->map_arr[y][x] == WALL)
				put_img(game, game->imgs->wall->img_ptr, x, y);
			else if (game->map->map_arr[y][x] == EXIT)
				put_img(game, game->imgs->exit->img_ptr, x, y);
			else if (game->map->map_arr[y][x] == COLLECT)
				put_img(game, game->imgs->collect->img_ptr, x, y);
		}
	}
	put_img(game, game->imgs->player->img_ptr,
			game->map->player_pos.x, game->map->player_pos.y);
}
