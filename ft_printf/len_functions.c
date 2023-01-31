#include "ft_printf.h"

size_t	unsigned_len(unsigned long long num)
{
	size_t	num_len;

	num_len = 1;
	while (num / ft_unsigned_pow(10, num_len - 1) >= 10)
		num_len++;
	return (num_len);
}

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}
size_t	num_len(int	num)
{
	size_t	n_len;

	n_len = 1;
	if (num == -2147483648)
		return (10);
	while (ft_abs(num) / ft_pow(10, n_len - 1) >= 10)
		n_len++;
	return(n_len);
}