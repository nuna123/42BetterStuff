
#include "ft_printf.h"

int	add_padding(t_format print_format, char type, char **toprint)
{
	int		padding_len;
	char	*padding;
	char	*padded_toprint;

	if (print_format.wdt > ft_strlen(*toprint))
	{
		padding = print_format.wdt - ft_strlen(*toprint);
		while (padding_len--)
		{
			if(print_format.zero)
				ft_strappend(&padding, "0");
			else
				ft_strappend(&padding, " ");
		}
		if(print_format.dash)
			padded_toprint = ft_strjoin(*toprint, padding);
		else
			padded_toprint = ft_strjoin(padding, *toprint);
		free(*toprint);
		*toprint = padded_toprint;
	}
	return (0);
}


int	apply_formats(t_format print_format, char type, char **toprint)
{
	int	stat_code;

	stat_code = 0;
	if (print_format.sign_pref)
		stat_code += add_sign(type, print_format.sign_pref, toprint);
	if (print_format.hash && !print_format.is_zero)
		stat_code += add_hex_pre(type, toprint);
	if (print_format.wdt)
		stat_code += add_padding(print_format, type, toprint);
	
	
	
	if (stat_code < 0)
		return (-1);
	return (0);
}
