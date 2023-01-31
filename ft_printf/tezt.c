#include "ft_printf.h"

static void	add_digit(char *dest, size_t n, int n_len)
{
	int		index;
	size_t	factor;
	int		digit;

	digit = 0;
	index = 0;
	factor = ft_pow(10, n_len - 1);
	while (index < n_len)
	{
		digit = 0;
		while (n >= factor)
		{
			digit += 1;
			n -= factor;
		}
		dest[index] = digit + '0';
		index++;
		factor /= 10;
	}
}

char	*unsigned_itoa(size_t num)
{
	int		num_len;
	char	*res;

	num_len = 1;

	while (num / ft_pow(10, num_len - 1) >= 10)
		num_len++;
	res = ft_calloc(num_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	add_digit(res, num, num_len);
	return (res);
}

int main(void)
{


	return 0;
}
