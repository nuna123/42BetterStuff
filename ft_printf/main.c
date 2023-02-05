#include "ft_printf.h"

int main(void)
{

	int i = ft_printf("1. %c", '0');
	printf("\n");
	int l = printf("1. %c", '0');

	printf("{%i}\n\n\n", i == l);
	i = ft_printf("2.  %c ", '0');
	printf("\n");
	l = printf("2.  %c ", '0');

	printf("{%i}\n\n\n", i == l);
	i = ft_printf("3.  %c", '0' - 256);
	printf("\n");
	l = printf("3.  %c", '0' - 256);

	printf("{%i}\n\n\n", i == l);
	i = ft_printf("4. %c ", '0' + 256);
	printf("\n");
	l = printf("4. %c ", '0' + 256);


	printf("{%i}\n\n\n", i == l);
	i = ft_printf("{5.  %c %c %c }", '0', 0, '1');
	printf("\n");
	l = printf("{5.  %c %c %c }", '0', 0, '1');

	printf("{%i}\n\n\n", i == l);
	i = ft_printf("6.  %c %c %c ", ' ', ' ', ' ');
	printf("\n");
	l = printf("6.  %c %c %c ", ' ', ' ', ' ');

	printf("{%i}\n\n\n", i == l);
	i = ft_printf("7.  %c %c %c ", '1', '2', '3');
	printf("\n");
	l = printf("7.  %c %c %c ", '1', '2', '3');

	printf("{%i}\n\n\n", i == l);
	i = ft_printf("8.  %c %c %c ", '2', '1', 0);
	printf("\n");
	l = printf("8.  %c %c %c ", '2', '1', 0);

	printf("{%i}\n\n\n", i == l);
	i = ft_printf("9.  %c %c %c ", 0, '1', '2');
	printf("\n");
	l = printf("9.  %c %c %c ", 0, '1', '2');

	printf("{%i}\n\n\n", i == l);
	return 0;
}
