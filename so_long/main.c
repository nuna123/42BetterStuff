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

int	keypress(int i, t_win *window)
{
	printf("KEY: {%i}\n", i);
	if (window && i == 65307)
	{
		mlx_destroy_window (window->mlx_ptr, window->win_ptr);
		exit(OK);
	}
	return (OK);
}

int main(void)
{
	t_win prog_ptr;
	
	prog_ptr = new_program(300, 300, "SO LONG");
	if (!prog_ptr.mlx_ptr || !prog_ptr.win_ptr)
		return (1);

	mlx_hook(prog_ptr.win_ptr, 17, 1L<<0, exit_nicely, &prog_ptr);
	mlx_hook(prog_ptr.win_ptr, 2, 1L<<0, keypress, &prog_ptr);
	mlx_loop(prog_ptr.mlx_ptr);
	return (OK);
}