
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "Libft/libft.h"

#define F_TYPS "cspdiuxX%"
#define F_FLGS "0123456789#-. "

//main file
int	ft_printf(const char *, ...);

//printing_funcs
int	print_char(int i);
int	print_str(char *s);
int	print_ptr(unsigned long long ptr);
int	print_int(int num);
int	print_unsigned_int(unsigned int num);
int	print_hex(unsigned int num, char type);

//utilities file
size_t	ft_pow(size_t nb, int power);
char	*unsigned_itoa(size_t num);


#endif