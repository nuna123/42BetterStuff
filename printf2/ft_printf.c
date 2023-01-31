
#include "ft_printf.h"
#include "Libft/libft.h"

int	add_sign(char type, char *typestr, char **toprint)
{
	char *newstr;

	if (type != 'd'
		&& type != 'i')
			return (-1);

	if(ft_isdigit(**toprint))
	{
		if (ft_strchr(typestr, '+'))
			newstr = ft_strjoin("+", *toprint);
		else
			newstr = ft_strjoin(" ", *toprint);
		free(toprint);
		*toprint = newstr;
	}
	return (0);
}

int	add_hex_pre(char type, char **toprint)
{
	char *newstr;

	if (type != 'x' && type != 'X')
		return (-1);
	if (!ft_memcmp(*toprint, "0", 2))
		return (0);
	if (type == 'X')
		newstr = ft_strjoin("0X", *toprint);
	else
		newstr = ft_strjoin("0X", *toprint);
	free(*toprint);
	*toprint = newstr;
	return (0);
}

/*
	gets cut str from grab_str, has to free it. 
	figures out where to send the argument
*/

int	print(char type, char *typestr, char *toprint)
{
	int status_code;

	status_code = 0;
	if (ft_strchr(typestr, '+')
		|| ft_strchr(typestr, ' '))
		status_code += add_sign(type, typestr, &toprint);

	if (ft_strchr(typestr, '#'))
		status_code += add_hex_pre(type, &toprint);
	
	return (0);
}


int	format_figureouter(va_list va_ptr, char *type_str, int *char_count)
{
	//int		tot_len;
	char	*toprint;
	if (!type_str)
		return (-1);
	if (ft_strlen(type_str) == 1)
	{
		if (type_str[0] == 'c')
			toprint = print_char(va_arg(va_ptr, int));
		else if (type_str[0] == 's')
			toprint = print_str(va_arg(va_ptr, char *));
		else if (type_str[0] == 'p')
			toprint = print_ptr(va_arg(va_ptr, void *));
		else if (type_str[0] == 'd'
			|| type_str[0] == 'i')
			toprint = print_int(va_arg(va_ptr, int));
		else if (type_str[0] == 'u')
			toprint = print_unsigned_int(va_arg(va_ptr, unsigned int));
		else if (type_str[0] == 'x'
				|| type_str[0] == 'X')
			toprint = print_hex(va_arg(va_ptr, unsigned int), type_str[0]);
		else if (type_str[0] == '%')
			toprint = print_char('%');
	}
	free(type_str);
	print(type_str[ft_strlen(toprint) - 1],type_str, toprint);
	*char_count += ft_strlen(toprint);
	free(toprint);
	return (1);
}

char *grab_str(char *str)
{
	int	s_len;

	s_len = 1;
	while(str[s_len]
		&& ft_strchr(F_FLGS, str[s_len])
		&& !ft_strchr(F_TYPS, str[s_len]))
		s_len++;
	if (!ft_strchr(F_FLGS, str[s_len]) && !ft_strchr(F_TYPS, str[s_len]))
		return (NULL);
	if (ft_strchr(F_TYPS, str[s_len]))
		s_len++;
	return(ft_substr(str, 0, s_len));
}

int	ft_printf(const char *str, ...)
{
	va_list	va_ptr;
	int		i;
	int		char_counter;
	int		stat_code;

	i = 0;
	char_counter = 0;
	va_start(va_ptr, str);
	// read through string
	// print each character until reaching '%'
	// when finding it, grab string that follows,
	//	shoot to printer function

	while (str[i])
	{
		if (str[i] == '%')
		{
			stat_code = format_figureouter(va_ptr, grab_str((char *)&str[i + 1]), &char_counter);
			if(stat_code == -1)
				return (0);
			i += stat_code;
		}
		else
			print_char(str[i]);
		i++;
	}
	va_end(va_ptr);
	return (0);
}

/* 
int main(void)
{
	int i = 4;

	printf("{%x}", 4);
	printf("\n\n\n");
	return 0;
}
 */