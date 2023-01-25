#include <stdio.h>
#include "get_next_line.h"


size_t	ft_strlen(const char *s)
{
	unsigned long	length;

	if (!s)
		return (0);
	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *) s;
	i = 0;
	if (!n)
		return ;
	while (i < n)
		*(p + i++) = 0;
	*p = 0;
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if ((nmemb * size) / size != nmemb)
		return (NULL);
	res = malloc(size * nmemb);
	if (!res)
		return (res);
	ft_bzero(res, size * nmemb);
	return (res);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char) c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

/*
	strjoin is modified to append str2 to str1,
	reallocate space and free the initial str1.
*/
void	ft_strjoin(char **s1, char const *s2)
{
	char	*ret_str;
	size_t	tot_len;
	size_t	i;

	tot_len = ft_strlen(*s1) + ft_strlen(s2);
	ret_str = (char *)ft_calloc(tot_len + 1, sizeof(char));
	if (!ret_str)
		return ;
	i = 0;
	while (i < tot_len)
	{
		if (i < ft_strlen(*s1))
			ret_str[i] = *(*(s1) + i);
		else
			ret_str[i] = s2[i - ft_strlen(*s1)];
		i++;
	}
	if (*s1)
		free(*s1);
	*s1 = ret_str;
}

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
	s[fd] = read_file(fd, s[fd]);
	if (!s[fd])
		return (NULL);
	line = get_line(s[fd]);
	s[fd] = update_s(s[fd]);
	return (line);
}

int main(int argc, char const *argv[])
{
	int fd = open("./file.txt", O_RDONLY);
	char *l = get_next_line(fd);

	while(l)
	{
		printf("LINE:{%s}\n", l);
		l = get_next_line(fd);
	}

	return 0;
}
