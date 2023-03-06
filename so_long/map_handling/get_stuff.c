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
	if (!found)
		return ((t_pos){0, 0, FALSE});
	return ((t_pos){pos.x, pos.y, TRUE});
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
