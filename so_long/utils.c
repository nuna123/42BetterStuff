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

void	free_game(t_game *game)
{
	free_map(game->map);
	free_imgs(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}

int	exit_nicely(t_game *game)
{
	if (game)
		free_game(game);
	exit(OK);
}

void	free_img(void *mlx_ptr, t_img *img)
{
	t_img	*next;

	if (img->img_ptr)
	{
		mlx_destroy_image(mlx_ptr, img->img_ptr);
		img->img_ptr = NULL;
		if (img->next_img)
		{
			next = img->next_img;
			img->next_img = NULL;
			free_img(mlx_ptr, next);
		}
		free(img);
	}
	
}

void	free_imgs(t_game *game)
{
	free_img(game->mlx_ptr, game->imgs->collect);
	free_img(game->mlx_ptr, game->imgs->wall);
	free_img(game->mlx_ptr, game->imgs->player);
	free_img(game->mlx_ptr, game->imgs->exit);
	free (game->imgs);
}