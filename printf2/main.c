#include "ft_printf.h"




size_t	ft_strlen(const char *s)
{
	unsigned long	length;

	if (!s)
		return (0);
	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

static int	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 1)
		return (nb);
	if (power == 0)
		return (1);
	return (nb * ft_pow(nb, power - 1));
}

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof (char) * ft_strlen(s) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static void	add_digit(char *dest, int n, int n_len)
{
	int	index;
	int	factor;
	int	digit;

	digit = 0;
	index = 0;
	factor = ft_pow(10, n_len - 1);
	if (n < 0)
	{
		n *= -1;
		dest[index++] = '-';
		n_len++;
	}
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

char	*ft_itoa(int n)
{
	int		n_len;
	char	*res;

	n_len = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	while (ft_abs(n) / ft_pow(10, n_len - 1) >= 10)
		n_len++;
	if (n < 0)
		res = ft_calloc(sizeof(char), n_len + 2);
	else
		res = ft_calloc(sizeof(char), n_len + 1);
	if (!res)
		return (NULL);
	add_digit(res, n, n_len);
	return (res);
}




void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *) s;
	i = 0;
	if (!n)
		return ;
	while (i < n)
		*(p + i++) = 0;
	*p = 0;
}


void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;

	if (nmemb && size)
	{
		if ((nmemb * size) / size != nmemb)
			return (NULL);
	}
	res = malloc(size * nmemb);
	if (!res)
		return (NULL);
	ft_bzero(res, size * nmemb);
	return (res);
}


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
	(void) ptr;
	return (0);
}

int	print_int(int num)
{
	char	*itoed;
	int		res;

	itoed = ft_itoa(num);
	res = print_str(itoed);
	return (res);
}

int	print_unsigned_int(unsigned int num)
{
	(void) num;
	return (0);
}

int	print_hex(unsigned int num, char type)
{
	(void) num;
	(void) type;
	return (0);
}



/* char *grab_str(char *s)
{
	char	*res;
	int		i;

	while(s[i] && s[i] != '\n')
		i++;
	res = ft_calloc(i, sizeof(char));
	if(!res)
		return (NULL);
	ft_strlcpy(s, res, i + 1);
	return (res);
}
 */
int	printer(va_list va_ptr, char *type_str)
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
	return (tot_len);
}

int ft_printf(const char *str, ...)
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
			stat_code = printer(va_ptr, (char *) &(str[i + 1]));
			if(stat_code == -1)
				return (0);
			char_counter += stat_code;
			i ++;
		}
		else
			print_char(str[i]);
		i++;
	}
	va_end(va_ptr);
	return (char_counter);
}


int main(int argc, char const *argv[])
{
	ft_printf("hello%c", 'M');
	return 0;
}
