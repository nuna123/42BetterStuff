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



void	move(t_game *game, int dir_x, int dir_y)
{
	t_pos	player;
	char	chosen_one;

	player = game->map->player_pos;
	chosen_one = game->map->map_arr[player.y + dir_y][player.x + dir_x];
	if (chosen_one != WALL)
	{
			// IF collectible, collect
			/*
			collect func needs to remove from collect arr, 
			remove from collect num
				if last collectible, activate exit
			*/
		if (chosen_one == COLLECT)
		{
			//do the do
		}
		// update map arr, update player position in t_map
		// if exit && exit active, exit nicely
		if (chosen_one == EXIT && game->map->exit_pos.is_last)

	}
}

int	keypress(int keypress, t_game *game)
{
	if (keypress == KEY_DOWN)
		ft_printf("DOWN KEY\n");
	else if (keypress == KEY_UP)
		ft_printf("UP KEY\n");
	else if (keypress == KEY_RIGHT)
		ft_printf("RIGHT KEY\n");
	else if (keypress == KEY_LEFT)
		ft_printf("LEFT KEY\n");
	else if (keypress == KEY_ESC)
		ft_printf("ESC KEY - leaving...\n");
	else
		printf("KEY: {%i}\n", keypress);
	if (game && keypress == KEY_ESC)
		exit_nicely(game);
	return (OK);
}

int main(int argc, char *argv[])
{
	t_game	*game;
	t_map	*map;

	map = make_map(argc, argv);
	if (!map)
		return (1);
	game = new_game(map->map_x * IMG_SIZE, map->map_y * IMG_SIZE,  "SO LONG");
	if (!game->mlx_ptr || !game->win_ptr)
		return (1);
	game->map = map;
	print_map(game->map);

	game->imgs = make_imgs(game);
	put_map(game);

	mlx_hook(game->win_ptr, 17, 1L<<0, exit_nicely, game); // X button
	mlx_hook(game->win_ptr, 2, 1L<<0, keypress, game); // keypress

	mlx_loop(game->mlx_ptr);

	free_map(game->map);
	return (OK);
}