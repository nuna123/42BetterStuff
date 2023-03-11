#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 9
#endif

void ft_strcpy(char *src, char *dest)
{
	if (!src || !*src)
		dest[0] = 0;
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
		*dest = 0;
	}
}

char *ft_strchr(char *src, char c)
{
	while (*src)
	{
		if (*src == c)
			return (src);
		src++;
	}
	if (*src == c)
		return (src);
	return (NULL);
}

char	*get_next_line(int fd)
{
	if (BUFFER_SIZE <= 0 || fd < 0)
		return(NULL);

	static char	*leftover;
	if (!leftover)
	{
		leftover = malloc(100000);
		leftover[0] = '\0';
	}

	char *buffer = malloc(100000); // into which read will read//	printf("\nLEFTOVER: {%s}\n", leftover);
	char *line = malloc(100000); // append buffer into this
	ft_strcpy(leftover, line);
	leftover[0] = 0;

	char *line_end = ft_strchr(line, 0);
	int rd = 0;

	while((rd = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[rd] = 0;
		ft_strcpy(buffer, line_end);
		line_end = ft_strchr(line, 0);
		if (ft_strchr(line, '\n'))
			break;
	}

	if (rd == 0 && !line[0]) 				// nothing was read
		return(free(buffer), free(leftover), leftover = NULL, free(line), NULL);
	if (rd == -1)							// reading err
		return(free(buffer), free(leftover), leftover = NULL, free(line), NULL);
	if (rd == 0)							//reached end of file
		return(free(buffer), free(leftover), leftover = NULL, line);

	//otherwise, copy leftover to leftover static var, null terminate LINE and return it
	line_end = ft_strchr(line, '\n') + 1;
	ft_strcpy(line_end, leftover);
	*line_end = '\0';
	return(free(buffer), line);
}
