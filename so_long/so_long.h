/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:04:30 by nroth             #+#    #+#             */
/*   Updated: 2023/03/02 16:15:58 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>

# include "minilibx-linux/mlx.h"
# include "libft.h"

# include "map_handling/map_handling.h"
# include "includes/vars_and_defins.h"
# include "includes/mlx_structs.h"

//////////// INIT STUFF //////////////////////////////

//init the game struct, which holds all the pointers and structs needed
t_game	*new_game(int window_width, int window_height, char *str);
//starts the right map based on argc and argv, the actual map filing and
//allocation is in map_handling folder&lib
t_map	*make_map(int argc, char *argv[]);
//img struct which holds all the info needed about an image. wtf is endian
t_img	*make_img(void *mlx, char *img_path);
// imgs struct holds t_img pointers to wall, player, collectible and exit imgs
t_imgs	*make_imgs(t_game *game);

//////////// PUT STUFF //////////////////////////////

//puts image on window smh
void	put_img(t_game *game, void *img_ptr, int x, int y);
//puts the map on window based on the game->map->arr. uses put_img()
void	put_map(t_game *game);
//updates player image for the fake animation thingy
int		update_player(t_game *game);
//when collectibles is 0 this is activated, updates exit img ptr to open
void	open_exit(t_game *game);

///////// UTILS ///////////////

//frees the game struct and all allocated stuff in it (hopefully)
void	free_game(t_game *game);
// frees everything, destroyes window, exits with status 0
int		exit_nicely(t_game *game);
// theres an mlx_destrpy_img function??? i am using it,
//but should probably research more
void	free_img(void *mlx_ptr, t_img *img);
//uses free_img on each thingy in the struct, frees struct
void	free_imgs(t_game *game);

/* Events
	KeyPress => 02
	KeyRelease => 03
	ButtonPress => 04
	ButtonRelease => 05
	MotionNotify => 06
	EnterNotify => 07
	LeaveNotify => 08
	FocusIn => 09
	FocusOut => 10
	KeymapNotify => 11
	Expose => 12
	GraphicsExpose => 13
	NoExpose => 14
	VisibilityNotify => 15
	CreateNotify => 16
	DestroyNotify => 17
	UnmapNotify => 18
	MapNotify => 19
	MapRequest => 20
	ReparentNotify => 21
	ConfigureNotify => 22
	ConfigureRequest => 23
	GravityNotify => 24
	ResizeRequest => 25
 */

/* Masks
	NoEventMask  => 0L
	KeyPressMask => 1L<<0
	KeyReleaseMask => 1L<<1
	ButtonPressMask  => 1L<<2 
	ButtonReleaseMask => 1L<<3  
	EnterWindowMask => 1L<<4
	LeaveWindowMask => 1L<<5
	PointerMotionMask => 1L<<6
	PointerMotionHintMask => 1L<<7
	Button1MotionMask => 1L<<8
	Button2MotionMask => 1L<<9
	Button3MotionMask => 1L<<10
	Button4MotionMask => 1L<<11
	Button5MotionMask => 1L<<12
	ButtonMotionMask =>1L<<13
	KeymapStateMask => 1L<<14
	 ExposureMask => 1L<<15
	VisibilityChangeMask => 1L<<16
	StructureNotifyMask => 1L<<17
	ResizeRedirectMask => 1L<<18
	SubstructureNotifyMask => 1L<<19
	SubstructureRedirectMask => 1L<<20
	FocusChangeMask => 1L<<21
	PropertyChangeMask => 1L<<22
	ColormapChangeMask => 1L<<23
	OwnerGrabButtonMask => 1L<<24

 */

#endif