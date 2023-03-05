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
		ft_printf("moves: %i\n", ++game->moves);
		if (chosen_one == COLLECT && game->map->collect_num > 0)
		{
			game->map->map_arr[player.y + dir_y][player.x + dir_x] = EMPTY;
			game->map->collect_num--;
		}
		if (game->map->collect_num == 0)
			open_exit(game);
		game->map->player_pos.x = player.x + dir_x;
		game->map->player_pos.y = player.y + dir_y;
		if (chosen_one == EXIT && !game->map->collect_num)
		{
			ft_printf("~~~~~~YOU WON! (yay)\n");
			exit_nicely(game);
		}
		put_map(game);
	}
}

int	keypress(int keypress, t_game *game)
{
	if (keypress == KEY_DOWN)
		move(game, 0, 1);
	else if (keypress == KEY_UP)
		move(game, 0, -1);
	else if (keypress == KEY_RIGHT)
		move(game, 1, 0);
	else if (keypress == KEY_LEFT)
		move(game, -1, 0);
	else if (keypress == KEY_ESC)
		ft_printf("ESC KEY - leaving...\n");
	if (game && keypress == KEY_ESC)
		exit_nicely(game);
	return (OK);
}

void	hooker(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 1L << 0, exit_nicely, game);
	mlx_hook(game->win_ptr, 2, 1L << 0, keypress, game);
	mlx_loop_hook(game->mlx_ptr, update_player, game);
	mlx_loop(game->mlx_ptr);
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	t_map	*map;

	map = make_map(argc, argv);
	if (!map)
		return (1);
	game = new_game(map->map_x * IMG_SIZE, map->map_y * IMG_SIZE, "SO LONG");
	if (!game->mlx_ptr || !game->win_ptr)
		return (1);
	game->map = map;
	game->imgs = make_imgs(game);
	put_map(game);
	hooker(game);
	return (OK);
}
