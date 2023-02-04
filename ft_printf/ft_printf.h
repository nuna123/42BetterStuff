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
	size_t	wdt;		// width
	int		prc;		// precision
	int		zero;		// zero padding
	int		pnt;		// .
	int		dash;		// -
	int		hash;		// #
	int		sign_pref;		// 0 = none; 1 = add '+'; 2 = add ' '
	int		sign;		// 0 = is zero; 1 = pos; -1 = neg
}t_format;

#define F_TYPS "cspdiuxX%"
#define F_FLGS "0#-+. "

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
void	ft_strappend(char **s1, char const *s2);

//len functions
unsigned int	unsigned_len(unsigned long long num);
unsigned int	num_len(int	num);


//flagifier funcs
int	add_hex_pre(char type, char **toprint);
int	add_sign(char type, int sign_pref, char **toprint);

t_format	*flagifier(char *typestr, char *toprint);
int	formatify(char *typestr, char **toprint);

//format applier
int	apply_formats(t_format print_format, char type, char **toprint);


#endif