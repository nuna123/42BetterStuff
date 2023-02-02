/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:31:31 by nroth             #+#    #+#             */
/*   Updated: 2023/01/13 13:31:32 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	flagifier(char type, char *typestr, char **toprint)
{
	t_format	*print_format;
	int			i;

	i = 0;
	print_format = ft_calloc(1, sizeof(t_format));
	if (!print_format)
		return (1);
	while (typestr[i] != type)
	{
		if (typestr[i] == '.')
			print_format->pnt = 1;
	}
	
	return (ft_strlen(*toprint));
}

int main()
{
	char *a = "a";
	flagifier('c', "#c", &a);
	return (0);
}