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
	int		counter;

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
	&& (nptr[counter] >= '0' &&nptr[counter] <= '9') )
	{
		res = (res * 10) + (nptr[counter] - '0');
		counter++;
	}
	return (res * sign);
}
