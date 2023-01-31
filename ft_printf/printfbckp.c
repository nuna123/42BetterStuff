
#include "ft_printf.h"
#include "Libft/libft.h"

/*
	gets cut str from grab_str, has to free it. 
	figures out where to send the argument
*/
int	printer(va_list va_ptr, char *type_str, int *char_count)
{
	int tot_len;
	if (!type_str)
		return (-1);
	if (ft_strlen(type_str) == 1)
	{
		if (type_str[0] == 'c')
			tot_len = print_char(va_arg(va_ptr, int));
		else if (type_str[0] == 's')
			tot_len = print_str(va_arg(va_ptr, char *));
		else if (type_str[0] == 'p')
			tot_len = print_ptr(va_arg(va_ptr, unsigned long long));
		else if (type_str[0] == 'd'
			|| type_str[0] == 'i')
			tot_len = print_int(va_arg(va_ptr, int));
		else if (type_str[0] == 'u')
			tot_len = print_unsigned_int(va_arg(va_ptr, unsigned int));
		else if (type_str[0] == 'x'
				|| type_str[0] == 'X')
			tot_len = print_hex(va_arg(va_ptr, unsigned int), type_str[0]);
		else if (type_str[0] == '%')
			tot_len = print_char('%');
	}
	free(type_str);
	return (tot_len + *char_count);
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
			stat_code = printer(va_ptr, grab_str((char *)&str[i + 1]), &char_counter);
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


int main(void)
{
	int i = 4;

	printf("{%x}", 4);
	printf("\n\n\n");
	return 0;
}
