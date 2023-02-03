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

#include "ft_printf.h"
#include "Libft/libft.h"

/*
	gets cut str from grab_str, has to free it. 
	figures out where to send the argument
*/


char	*get_string(va_list va_ptr, char *type_str, int type_len)
{
	char	*toprint;

	if (!type_str)
		return (NULL);
	toprint = NULL;
	if (type_str[type_len] == 'c')
		toprint = print_char(va_arg(va_ptr, int));
	else if (type_str[type_len] == 's')
		toprint = print_str(va_arg(va_ptr, char *));
	else if (type_str[type_len] == 'p')
		toprint = print_ptr(va_arg(va_ptr, unsigned long long));
	else if (type_str[type_len] == 'd'
		|| type_str[type_len] == 'i')
		toprint = print_int(va_arg(va_ptr, int));
	else if (type_str[type_len] == 'u')
		toprint = print_unsigned_int(va_arg(va_ptr, unsigned int));
	else if (type_str[type_len] == 'x'
		|| type_str[type_len] == 'X')
		toprint = print_hex(va_arg(va_ptr, unsigned int), type_str[type_len]);
	else if (type_str[type_len] == '%')
		toprint = print_char('%');
	return (toprint);
}

int	printer(va_list va_ptr, char *type_str, int *char_count)
{
	char	*toprint;
	int		type_len;

	if (!type_str)
		return (-1);
	type_len = ft_strlen(type_str) - 1;
	toprint = get_string(va_ptr, type_str, type_len);
	if (!toprint)
		return (-1);
	if (ft_strlen(type_str) > 1)
		flagifier(type_str[type_len], type_str, &toprint);
	ft_putstr_fd(toprint, 1);
	*char_count += ft_strlen(toprint);
	free(toprint);
	free(type_str);
	return (type_len + 1);
}

char	*grab_str(char *str)
{
	int	s_len;

	s_len = 0;
	while (str[s_len]
		&& (ft_strchr(F_FLGS, str[s_len])
			|| !ft_isdigit(str[s_len])))
		s_len++;
	if (!ft_strchr(F_FLGS, str[s_len]) 
		&& !ft_strchr(F_TYPS, str[s_len])
		&& !ft_isdigit(str[s_len]))
		return (NULL);
	if (ft_strchr(F_TYPS, str[s_len]))
		s_len++;
	return (ft_substr(str, 0, s_len));
}

	// read through string
	// print each character until reaching '%'
	// when finding it, grab string that follows,
	//	shoot to printer function
int	ft_printf(const char *str, ...)
{
	va_list	va_ptr;
	int		i;
	int		char_cnt;
	int		s_code;

	i = -1;
	char_cnt = 0;
	va_start(va_ptr, str);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			s_code = printer(va_ptr, grab_str((char *)&str[i + 1]), &char_cnt);
			if (s_code == -1)
				return (0);
			i += s_code;
		}
		else
		{
			char_cnt++;
			write(1, &str[i], 1);
		}
	}
	va_end(va_ptr);
	return (char_cnt);
}

int main(void)
{
	int i = 4;


	//int ret = ft_printf("HI{%#rx}\n", i);
	int ret2 = printf("HI{%#x}\n", i);
	//ft_printf("ret: {%i}\n", ret);
	ft_printf("ret2: {%i}\n", ret2);

	//printf("ME{%s}", );
	//printf("\n\n\n");
	return 0;
}
