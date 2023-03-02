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
# include "Libft/libft.h"
# include "map_handling/map_handling.h"

# define OK 0
# define ERR 1

# define KEY_LEFT 97
# define KEY_DOWN 115
# define KEY_RIGHT 100
# define KEY_UP 119

# define KEY_ESC 65307

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
}		t_win;

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