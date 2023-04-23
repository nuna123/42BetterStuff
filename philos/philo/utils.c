/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:21:16 by nroth             #+#    #+#             */
/*   Updated: 2023/03/11 10:21:17 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	ft_strlen(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

long	ft_atoi(const char *nptr)
{
	long int	res;
	int			sign;
	int			counter;

	res = 0;
	sign = 1;
	counter = 0;
	while ((nptr[counter] >= 9 && nptr[counter] <= 13)
		|| nptr[counter] == ' ')
		counter++;
	if (nptr[counter] == '-'
		|| nptr[counter] == '+')
		sign = 44 - nptr[counter++];
	while (counter < ft_strlen(nptr)
		&& (nptr[counter] >= '0' && nptr[counter] <= '9'))
	{
		res = (res * 10) + (nptr[counter] - '0');
		counter++;
	}
	return (res * sign);
}

unsigned long	get_timestamp_ms(t_time *time)
{
	unsigned long	ms_timestamp;
	t_time			ts;

	gettimeofday(&ts, NULL);
	if (!time)
		ms_timestamp = (1000 * ts.tv_sec) + (ts.tv_usec / 1000);
	else
		ms_timestamp = (1000 * time->tv_sec) + (time->tv_usec / 1000);
	return (ms_timestamp);
}

unsigned long	msleep(unsigned long ms)
{
	return (usleep(ms * 1000));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			counter;
	unsigned char	chars[2];

	counter = 0;
	while (counter < n && (s1[counter] || s2[counter]))
	{
		chars[0] = s1[counter];
		chars[1] = s2[counter];
		if (chars[0] - chars[1])
			return ((chars[0] - chars[1]));
		counter++;
	}
	return (0);
}
