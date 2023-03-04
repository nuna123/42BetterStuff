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
	free(game->imgs->collect);
	free(game->imgs->player);
	free(game->imgs->exit);
	free(game->imgs->wall);
	free(game->imgs);
	free(game);
}

int	exit_nicely(t_game *game)
{
	if (game)
	{
		mlx_destroy_window (game->mlx_ptr, game->win_ptr);
		free_game(game);
	}
	exit(OK);
}
