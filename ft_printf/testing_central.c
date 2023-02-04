
#include "ft_printf.h"



void	ft_strappend(char **s1, char const *s2)
{
	char	*ret_str;
	size_t	tot_len;
	size_t	i;

	size_t s1len = ft_strlen(*s1);
	size_t s2len = ft_strlen(s2);
	tot_len =  s1len + s2len;
	ret_str = (char *)ft_calloc(tot_len + 1, sizeof(char));
	if (!ret_str)
		return ;
	i = 0;
	while (i < tot_len)
	{
		if (i < ft_strlen(*s1))
			ret_str[i] = *(*(s1) + i);
		else
			ret_str[i] = s2[i - ft_strlen(*s1)];
		i++;
	}
	if (*s1)
		free(*s1);
	*s1 = ret_str;
}


int	add_sign(char type, int sign_pref, char **toprint)
{
	char	*newstr;

	if (type != 'd'
		&& type != 'i')
		return (-1);
	if (ft_isdigit(**toprint))
	{
		if (sign_pref == 1)
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
	char	*newstr;

	if (type != 'x' && type != 'X')
		return (-1);
	if (!ft_memcmp(*toprint, "0", 2))
		return (0);
	if (type == 'X')
		newstr = ft_strjoin("0X", *toprint);
	else
		newstr = ft_strjoin("0x", *toprint);
	free(*toprint);
	*toprint = newstr;
	return (0);
}




int	add_padding(t_format print_format, char type, char **toprint)
{
	int		padding_len;
	char	*padding;
	char	*padded_toprint;

	padding = NULL;
	if (print_format.wdt > ft_strlen(*toprint))
	{
		padding_len = print_format.wdt - ft_strlen(*toprint);
		while (padding_len--)
		{
			if (print_format.zero && !ft_strchr("sc", type))
				ft_strappend(&padding, "0");
			else
				ft_strappend(&padding, " ");
		}
		if (print_format.dash)
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
	if (print_format.sign_pref && print_format.sign > 0)
		stat_code += add_sign(type, print_format.sign_pref, toprint);
	if (print_format.hash && !print_format.sign)
		stat_code += add_hex_pre(type, toprint);
	if (print_format.wdt)
		stat_code += add_padding(print_format, type, toprint);

	if (stat_code < 0)
		return (-1);
	return (0);
}




static void	flagifier_2(char *typestr, t_format *print_format, char *toprint)
{
	int	i;

	if (ft_atoi(toprint) < 0)
		print_format->sign = -1;
	else if (ft_atoi(toprint) > 0)
		print_format->sign = 1;
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
/*
	builds the t_format object with all the formatting properties
*/

t_format	*flagifier(char *typestr, char *toprint)
{
	t_format	*print_format;
	int			i;

	i = -1;
	print_format = ft_calloc(1, sizeof(t_format));
	if (!print_format)
		return (NULL);
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
	flagifier_2(&typestr[i], print_format, toprint);
	return (print_format);
}

int	check_if_ok(t_format *print_format)
{
	(void)print_format;
	return (0);
}

int	formatify(char *typestr, char **toprint)
{
	t_format	*print_format;

	print_format = flagifier(typestr, *toprint);
	if (!print_format || check_if_ok(print_format) == -1)
		return (-1);
	apply_formats(*print_format,
		typestr[ft_strlen(typestr) - 1],
		toprint);
	return (0);
}


int main(void)
{
	char *str = ft_strdup("HI");
	formatify("#03.4s", &str);
	return (0);
}