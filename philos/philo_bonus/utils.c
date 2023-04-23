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

long	ft_atoi(const char *nptr)
{
	long int	res;
	int			sign;
	int			counter;
	int			strlen;

	res = 0;
	sign = 1;
	counter = 0;
	strlen = 0;
	while (nptr[strlen])
		strlen++;
	while ((nptr[counter] >= 9 && nptr[counter] <= 13)
		|| nptr[counter] == ' ')
		counter++;
	if (nptr[counter] == '-'
		|| nptr[counter] == '+')
		sign = 44 - nptr[counter++];
	while (counter < strlen
		&& (nptr[counter] >= '0' && nptr[counter] <= '9'))
	{
		res = (res * 10) + (nptr[counter] - '0');
		counter++;
	}
	return (res * sign);
}

unsigned long	get_timestamp_ms(void)
{
	unsigned long	ms_timestamp;
	t_time			ts;

	gettimeofday(&ts, NULL);
	ms_timestamp = (1000 * ts.tv_sec) + (ts.tv_usec / 1000);
	return (ms_timestamp);
}

unsigned long	msleep(unsigned long ms)
{
	return (usleep(ms * 1000));
}

void	free_prog(t_prog *prog)
{
	sem_close(prog->print_sema);
	sem_close(prog->forks_sema);
	free (prog->philos);
	free (prog->philo_pids);
	free (prog);
}
