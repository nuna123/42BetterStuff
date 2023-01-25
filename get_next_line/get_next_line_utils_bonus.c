/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:12 by nroth             #+#    #+#             */
/*   Updated: 2023/01/17 10:50:14 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	ft_bzero((char *)s2, BUFFER_SIZE);
	*s1 = ret_str;
}
