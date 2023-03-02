/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:11 by nroth             #+#    #+#             */
/*   Updated: 2023/03/02 16:48:20 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_handling.h"

int	close_and_return(int fd, int ret_val)
{
	close (fd);
	return (ret_val);
}

int	is_all_char(char *s, char c, void (*f)(void *arg))
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		if (c != s[i])
		{
			if (f)
				free (s);
			return (ERR);
		}
		i++;
	}
	if (f)
		f(s);
	return (OK);
}

t_map	*map_bzero(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->map_arr = NULL;
	map->map_y = 0;
	map->map_x = 0;
	map->collectibles_num = 0;
	map->exit.x = 0;
	map->exit.y = 0;
	map->exit.is_last = TRUE;
	map->start_pos.x = 0;
	map->start_pos.y = 0;
	map->start_pos.is_last = TRUE;
	map->collectibles = NULL;
	map->collectibles_num = 0;
	return (map);
}

void	free_arr(char **arr, int arr_size)
{
	int	i;

	if (!arr_size)
		arr_size = INT_MAX;
	i = 0;
	while (i < arr_size && arr[i])
		free(arr[i++]);
	free(arr);
}

int	arr_len(char **arr)
{
	int	cnt;

	if (!arr)
		return (0);
	cnt = 0;
	while (arr[cnt])
		cnt++;
	return (cnt);
}
