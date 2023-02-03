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

static void	flagifier_2(char *typestr, t_format *print_format)
{
	int	i;

	i = -1;
	while (ft_isdigit(typestr[++i]) || typestr[i] == '.')
	{
		if (typestr[i] == '.')
			print_format->pnt = 1;
		else
		{
			if (!print_format->pnt)
			{
				print_format->wdt = ft_atoi(&typestr[i]);
				i += num_len(print_format->wdt) - 1;
			}
			else
			{
				print_format->prc = ft_atoi(&typestr[i]);
				i += num_len(print_format->prc) - 1;
			}
		}
	}
}

t_format	*flagifier(char *typestr, char *toprint)
{
	t_format	*print_format;
	int			i;

	i = -1;
	print_format = ft_calloc(1, sizeof(t_format));
	if (!print_format)
		return (NULL);
	print_format->is_zero = !ft_strncmp("0", toprint, 2);
	while (ft_strchr(F_FLGS, typestr[++i]))
	{
		if (typestr[i] == '0')
			print_format->zero = 1;
		if (typestr[i] == '+' && !print_format->sign_pref)
			print_format->sign_pref = 1;
		if (typestr[i] == ' ' && !print_format->sign_pref)
			print_format->sign_pref = 2;
		if (typestr[i] == '#')
			print_format->hash = 1;
		if (typestr[i] == '-')
			print_format->dash = 1;
		if (typestr[i] == '.')
			print_format->pnt = 1;
	}
	flagifier_2(&typestr[i], print_format);
	return (print_format);
}

int check_if_ok(t_format *print_format)
{
	(void *)print_format;
	return (0);
}

int	formatify(char *typestr, char **toprint)
{
	t_format *print_format;

	print_format = flagifier(typestr, toprint);
	if (!print_format || check_if_ok(print_format) == -1)
		return (-1);
	apply_formats(print_format,
		typestr[ft_strlen(typestr) - 1],
		toprint);
}
