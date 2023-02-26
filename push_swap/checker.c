/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:45:12 by nroth             #+#    #+#             */
/*   Updated: 2023/02/26 17:56:32 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buffer[22];

	ft_bzero(buffer, 22);
	while (read(STDOUT_FILENO, buffer, 2) > 0)
	{
		ft_printf("%s", buffer);
		ft_bzero(buffer, 22);
		
	}
	ft_printf("%s!!!\n", buffer);
	return (0);
}