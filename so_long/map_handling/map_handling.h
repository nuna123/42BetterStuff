/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:11 by nroth             #+#    #+#             */
/*   Updated: 2023/03/02 17:01:02 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HANDLING_H
# define MAP_HANDLING_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>

# include "../Libft/libft.h"
# include "../includes/map_structs.h"
# include "../includes/vars_and_defins.h"

//	MAP HANDLING UTILS
int			close_and_return(int fd, int ret_val);
int			is_all_char(char *s, char c, void (*f)(void *arg));
t_map		*map_bzero(void);
void		free_arr(char **arr, int arr_size);
int			arr_len(char **arr);

// GET STUFF
int			collecties_expand(char *line, t_pos *x_y, t_pos *collecties);
t_pos		*get_collectibles(char *map_path, int collect_num);
t_pos		get_char_pos(char *path_to_file, char c);
int			count_char(char *path_to_file, char c);
int			count_lines(char *path);

// FILL AND CHECK
void		f_fill(char **tab, int *c_e_s, t_map *map, t_pos pos);
int			flood_fill(t_map *map);
int			check_line_validity(char *map_line, int x);
int			check_map_components(char *map_path);
int			check_map_validity(char *map_path);

// MAP_HANDLING
// void		print_map(t_map *map);
void		fill_map_arr(char *map_path, t_map *map);

t_map		*map_fill(char *map_path);
void		*free_map(t_map *map);
t_map		*process_map(char *map_path);

//MAIN FUNC, DELETE PRINTMAAP FOR NORM
int			map_handling(char *map_path);

#endif