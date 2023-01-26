#include "ft_printf.h"

/*
	get cut format str, send to printing funcd
	updates char count to add however many chars were printed
	returns format str len, -1 on err
	FREE format str
*/
int	print_format(char *format_str, int *char_count);
/*
	get format str from s[i] up until its end, allocate it
	can either be one letter or a bunch of numbers/points/flags
	return it
*/
char *grab_f_str(char *s)
{
	int		f_str_len;
	char	*ret_str;

	f_str_len = 0;
	while (ft_strchr(s, s[f_str_len]))
		f_str_len++;
	ret_str = ft_calloc(f_str_len + 1, sizeof(char));
	if (!ret_str)
		return (NULL);
	ft_substr
}
int	ft_printf(const char *str, ...)
{
	int	char_count;
	int	i;
	va_list va_ptr;

	i = 0;
	char_count = 0;
	va_start(va_ptr, str);

	while (str[i] && char_count >= 0)
	{
		if (str[i] == '%')
		{
			//get format str len
			// printthe stuff, check output len
			// i+= format str len
			// char_count += output len
			i += print_format(grab_f_str(str[i + 1]), &char_count);			
		}
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(va_ptr);
	return (char_count);
}