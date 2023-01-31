
#include "ft_printf.h"

int	print_char(int i)
{
	char c;

	c = (char) i;
	write(1, &c, 1);
	return (1);
}

int	print_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	print_ptr(unsigned long long ptr)
{
	printf("%p", ptr);
	return (0);
}

int	print_int(int num)
{
	char	*itoed;
	int		res;

	itoed = ft_itoa(num);
	res = print_str(itoed);
	free(itoed);
	return (res);
}

int	print_unsigned_int(unsigned int num)
{
	char	*itoed;
	int		res;

	itoed = ft_unsigned_itoa(num);
	res = print_str(itoed);
	free(itoed);
	return (res);

}

int	print_hex(unsigned int num, char type)
{
	(void) num;
	(void) type; // Xcaps or x small
	return (0);
}