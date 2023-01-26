/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:16:12 by nroth             #+#    #+#             */
/*   Updated: 2023/01/26 13:16:13 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#define POSSIBLE_FLGS="cspdiuxX0123456789-+ #"

#include <stdarg.h>
#include <stdio.h>

#include "./Libft/libft.h"

//MAINFILE
int	ft_printf(const char *str, ...);

#endif
