/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:31:31 by nroth             #+#    #+#             */
/*   Updated: 2023/01/13 13:31:32 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "Libft/libft.h"

typedef struct s_format{
	int	wdt;		// width
	int	prc;		// precision
	int	zero;		// zero padding
	int	pnt;		// .
	int	dash;   	// -
	int	sign;   	// pos or neg number
	int	is_zero;	// is number zero
	int	perc;   	// %
	int	sp;	 	// space flag ' '
}t_format;

#define F_TYPS "cspdiuxX%"
#define F_FLGS "0123456789#-. "

#define HEX_CAP	"0123456789ABCDEF"
#define HEX_SMOL	"0123456789abcdef"

//main file
int	ft_printf(const char *, ...);

//printing_funcs
char			*print_char(int i);
char			*print_str(char *s);
char			*print_ptr(unsigned long long ptr);
char			*print_int(int num);
char			*print_unsigned_int(unsigned int num);
char			*print_hex(unsigned int num, char type);

//utilities file
int				ft_pow(int nb, int power);
char			*unsigned_itoa(size_t num);
unsigned int	ft_unsigned_pow(size_t nb, int power);


//len functions
unsigned int	unsigned_len(unsigned long long num);
unsigned int	num_len(int	num);


int	flagifier(char type, char *typestr, char **toprint);
//flagifier funcs
int	add_sign(char type, char *typestr, char **toprint);
int	add_hex_pre(char type, char **toprint);


#endif