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

t_game	*new_game(int window_width, int window_height, char *str)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, window_width,
			window_height, str);
	return (game);
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

t_img	*make_img(void *mlx, char *img_path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img_ptr = mlx_xpm_file_to_image(mlx, img_path, &img->w, &img->h);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	return (img);
}

t_imgs	*make_imgs(t_game *game)
{
	t_imgs	*imgs;

	imgs = ft_calloc(1, sizeof(t_imgs));
	imgs->player = make_img(game->mlx_ptr, PLAYER_IMG_PATH);
	imgs->wall = make_img(game->mlx_ptr, WALL_IMG_PATH);
	imgs->exit = make_img(game->mlx_ptr, EXIT_C_IMG_PATH);
	imgs->collect = make_img(game->mlx_ptr, COLLECT_IMG_PATH);
	return (imgs);
}
