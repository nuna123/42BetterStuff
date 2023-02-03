#include <stdio.h>
#include "ft_printf.h"

int main()
{
	printf("%i\n", ft_atoi("32.3c"));
	printf("%i\n", ft_atoi("3c"));
	return 0;
}
