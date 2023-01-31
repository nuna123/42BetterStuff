
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
char *print_char(int i);
char *print_str(char *s);
char *print_ptr(void *x);
char *print_int(int num);
char *print_unsigned_int(unsigned int num);
char *print_hex(unsigned int num, char type);

//utilities file
size_t	ft_pow(size_t nb, int power);
char	*unsigned_itoa(size_t num);
size_t	ft_unsigned_pow(size_t nb, int power);


//len functions

size_t	unsigned_len(unsigned long long num);
size_t	num_len(int	num);


#endif