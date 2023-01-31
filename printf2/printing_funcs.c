
#include "ft_printf.h"

char *print_char(int i)
{
	char c;

	c = (char) i;
	return (ft_strdup(&c));
}

char *print_str(char *s)
{
	return (ft_strdup(s));
}

char *print_ptr(void *ptr)
{
	printf("%p", ptr);
	return (0);
}

char *print_int(int num)
{
	return (ft_itoa(num));
}

char *print_unsigned_int(unsigned int num)
{
	return (unsigned_itoa(num));
}

char *print_hex(unsigned int num, char type)
{
	(void) num;
	(void) type; // Xcaps or x small
	return (0);
}