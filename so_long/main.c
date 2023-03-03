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

t_win new_program(int window_width, int window_height, char *str)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, window_width, window_height, str);
	return ((t_win) {mlx_ptr, win_ptr, window_width, window_height});
}

int	exit_nicely(t_win *window)
{
	if (window)
		mlx_destroy_window (window->mlx_ptr, window->win_ptr);
	exit(OK);
}

int	keypress(int keypress, t_win *window)
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
	if (window && keypress == KEY_ESC)
	{
		mlx_destroy_window (window->mlx_ptr, window->win_ptr);
		exit(OK);
	}
	return (OK);
}

t_map	*make_map(int argc, char *argv[])
{
	char	*map_path;
	t_map	*map;

	if (argc == 2)
		map_path = argv[1];
	else if (argc == 1)
		map_path = "./maps/map.ber";
	else
		exit(ERR);
	map = process_map(map_path);
	if (!map)
	{
		ft_printf ("MAP NOT OK:(\n\n");
		exit(ERR);
	}
	ft_printf ("MAP OK!\n\n");
	return (map);
}

int main(int argc, char *argv[])
{
	t_win	prog_ptr;
	t_map	*map;
	
	map = make_map(argc, argv);
	print_map(map);
	free_map(map);
	prog_ptr = new_program(300, 300, "SO LONG");
	if (!prog_ptr.mlx_ptr || !prog_ptr.win_ptr)
		return (1);
	mlx_hook(prog_ptr.win_ptr, 17, 1L<<0, exit_nicely, &prog_ptr);
	mlx_hook(prog_ptr.win_ptr, 2, 1L<<0, keypress, &prog_ptr);
	mlx_loop(prog_ptr.mlx_ptr);
	return (OK);
}