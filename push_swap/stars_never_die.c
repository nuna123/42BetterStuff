/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stars_never_die.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:12:54 by nroth             #+#    #+#             */
/*   Updated: 2023/02/22 20:12:56 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	recursively_print(t_list *stack_a, t_list *stack_b)
{
	t_list	*next_a;
	t_list	*next_b;

	next_a = NULL;
	next_b = NULL;
	if ((stack_a && stack_a->next) || (stack_b && stack_b->next))
	{
		if (stack_a && stack_a->next)
			next_a = stack_a->next;
		if (stack_b && stack_b->next)
			next_b = stack_b->next;
		recursively_print(next_a, next_b);
	}
	if (stack_a)
		ft_printf("  %-10i", (*(int *) stack_a->content));
	else
		ft_printf("");
	if (stack_b)
		ft_printf("%-10i\n", (*(int *) stack_b->content));
	else
		ft_printf("\n");
}

void	lst_print_but_complicated(t_list *stack_a, t_list *stack_b)
{
	ft_printf("----------------------\n");
	recursively_print(stack_a, stack_b);
	ft_printf("-------------------\n");
	ft_printf("  %s\t    %s  \n", "a", "b");
	ft_printf("----------------------\n\n");
}
