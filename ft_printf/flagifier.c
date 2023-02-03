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

/*
typedef struct s_format{
	int	wdt;		// width
	int	prc;		// precision
	int	zero;		// zero padding
	int	pnt;		// .
	int	dash;   	// -
	int	hash;   	// -
	int	sign_pref;   	// 0 = none; 1 = add '+'; 2 = add ' '
	int	is_zero;	// is number zero
}t_format;
*/

t_format	*flagifier(char *typestr, char *toprint)
{
	t_format	*print_format;
	int			i;

	i = -1;
	print_format = ft_calloc(1, sizeof(t_format));
	if (!print_format)
		return (1);
	if (ft_strncmp("0", toprint, 2) == 0)
		print_format->is_zero = 1;
	while (ft_strchr(F_FLGS, typestr[++i]))//"0#-+. "
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
	while (ft_isdigit(typestr[i]) || typestr[i] == '.')
	{
		if(typestr[i] == '.')
			print_format->pnt = 1;
		else
		{
			if(!print_format->pnt)
			{
				print_format->wdt = ft_atoi(&typestr[i]);
				i+= num_len(print_format->wdt - 1);
			}
			else
			{
				print_format->prc = ft_atoi(&typestr[i]);
				i+= num_len(print_format->prc - 1);
			}
		}
		i++;
	}


	return (print_format);
}
 



int main()
{
	char *a = "a";
	flagifier("#c", a);
	return (0);
}



/* 

print_format = ft_calloc(1, sizeof(t_format));
	if (!print_format)
		return (1);
	if (ft_strncmp("0", toprint, 2) == 0)
		print_format->is_zero = 1;
	while (ft_strchr(F_FLGS, typestr[++i]))//"0#-+. "
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
	while (ft_isdigit(typestr[i]) || typestr[i] == '.')
	{
		if(typestr[i] == '.')
			print_format->pnt = 1;
		else
		{
			if(!print_format->pnt)
			{
				print_format->wdt = ft_atoi(&typestr[i]);
				i+= num_len(print_format->wdt - 1);
			}
			else
			{
				print_format->prc = ft_atoi(&typestr[i]);
				i+= num_len(print_format->prc - 1);
			}
		}
		i++;
	}



 */