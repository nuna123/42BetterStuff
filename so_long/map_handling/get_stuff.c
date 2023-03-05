/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:43:11 by nroth             #+#    #+#             */
/*   Updated: 2023/03/02 16:51:06 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_handling.h"

int	collecties_expand(char *line, t_pos *x_y, t_pos *collecties)
{
	if (ft_strchr(&line[x_y->x], COLLECT))
	{
		x_y->x += (ft_strchr(&line[x_y->x], COLLECT) - &line[x_y->x]) + 1;
		*collecties = (t_pos){x_y->x - 1, x_y->y, FALSE};
		return (1);
	}
	else
		x_y->x = ft_strlen(line);
	return (0);
}

t_pos	*get_collectibles(char *map_path, int collect_num)
{
	t_pos	*collecties;
	int		fd;
	char	*line;
	t_pos	x_y;
	int		clct_cnt;

	collecties = ft_calloc(collect_num + 1, sizeof (t_pos));
	fd = open(map_path, O_RDONLY);
	clct_cnt = 0;
	line = get_next_line(fd);
	x_y = (t_pos){0, 0, FALSE};
	while (line)
	{
		x_y.x = 0;
		while (x_y.x < (int) ft_strlen(line))
			clct_cnt += collecties_expand(line, &x_y, &collecties[clct_cnt]);
		free(line);
		line = get_next_line(fd);
		x_y.y++;
	}
	collecties[collect_num].is_last = TRUE;
	close(fd);
	return (collecties);
}

t_pos	get_char_pos(char *path_to_file, char c)
{
	char	*line;
	t_pos	pos;
	int		fd;
	int		found;

	fd = open(path_to_file, O_RDONLY);
	line = get_next_line(fd);
	found = 0;
	pos.y = 0;
	while (line)
	{
		if (ft_strchr(line, c) && !found)
		{
			pos.x = (ft_strchr(line, c) - line);
			found = 1;
		}
		free(line);
		line = get_next_line(fd);
		if (!found)
			pos.y++;
	}
	close(fd);
	pos.is_last = TRUE;
	return (pos);
}

int	count_char(char *path_to_file, char c)
{
	char	*line;
	char	*lil_line;
	int		char_count;
	int		fd;

	fd = open(path_to_file, O_RDONLY);
	char_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lil_line = line;
		while (ft_strchr(lil_line, c))
		{
			char_count++;
			lil_line = ft_strchr(lil_line, c) + 1;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (close_and_return(fd, char_count));
}

int	count_lines(char *path)
{
	char	*line;
	int		lc;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (fd);
	lc = 0;
	line = get_next_line(fd);
	while (line)
	{
		lc++;
		free(line);
		line = get_next_line(fd);
	}
	return (close_and_return(fd, lc));
}
