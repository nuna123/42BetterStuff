/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:12 by nroth             #+#    #+#             */
/*   Updated: 2023/01/17 10:50:14 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *res)
{
	char	buffer[BUFFER_SIZE + 1];
	int		err_code;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	err_code = 1;
	while (err_code > 0 && !ft_strchr(res, '\n'))
	{
		err_code = read(fd, buffer, BUFFER_SIZE);
		if (err_code > 0)
		{
			ft_strjoin(&res, buffer);
			ft_bzero(buffer, BUFFER_SIZE);
		}
		else if (err_code == 0)
			break ;
		else if (err_code == -1)
		{
			if (res)
				free(res);
			return (NULL);
		}
	}
	return (res);
}

/*
	update s to remove the line read,
	freeing original and allocating whatever leftover is in s
*/
char	*update_s(char *s)
{
	int		i;
	char	*new_s;
	int		new_len;
	int		line_len;

	line_len = 0;
	while (s[line_len] && s[line_len] != '\n')
		line_len++;
	if (s[line_len] == '\n')
		line_len++;
	new_len = ft_strlen(s) - line_len;
	if (!new_len)
		free(s);
	if (!new_len)
		return (NULL);
	new_s = (char *) ft_calloc(new_len + 1, sizeof(char));
	if (!new_s)
		return (NULL);
	i = -1;
	while (++i < new_len)
		new_s[i] = s[line_len + i];
	free (s);
	return (new_s);
}

/*
	get the line from s, only up to \n or \0.
*/
char	*get_line(char *s)
{
	char	*line;
	int		line_len;
	int		i;

	line_len = 0;
	i = 0;
	while (s[line_len] && s[line_len] != '\n')
		line_len++;
	if (s[line_len] == '\n')
		line_len++;
	line = (char *) ft_calloc(line_len + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (i < line_len)
	{
		line[i] = s[i];
		i++;
	}
	return (line);
}

/*
	S is an array of character pointers, each one will be tied to the
	file descriptor as index. 
	this is to keep the read line of each file descriptor and appending to it.
*/

char	*get_next_line(int fd)
{
	static char	*s[FOPEN_MAX];
	char		*line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (read(fd, NULL, 0) == -1)
	{
		free (s[fd]);
		return (NULL);
	}
	s[fd] = read_file(fd, s[fd]);
	if (!s[fd])
		return (NULL);
	line = get_line(s[fd]);
	s[fd] = update_s(s[fd]);
	return (line);
}

/* 
int main()
{
	int fd = open("./file.txt", O_RDONLY);

	char *l = get_next_line(fd);
	printf("LINE: {%s}\n", l);
	if (l)
		free(l);
	
	
	l = get_next_line(fd);
	printf("LINE: {%s}\n", l);
	if (l)
		free(l);
	l = get_next_line(fd);
	printf("LINE: {%s}\n", l);
	if (l)
		free(l);
	l = get_next_line(fd);
	printf("LINE: {%s}\n", l);
	if (l)
		free(l);
	l = get_next_line(fd);
	printf("LINE: {%s}\n", l);
	if (l)
		free(l);
	return 0;
}
 */