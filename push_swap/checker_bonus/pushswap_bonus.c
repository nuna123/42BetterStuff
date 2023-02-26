/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_fileA.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:20:30 by nroth             #+#    #+#             */
/*   Updated: 2023/02/21 11:20:31 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	ps_s(t_list **stack)
{
	t_list	*temp;

	if (!stack || !*stack || !(*stack)->next)
		return (ERR);
	temp = *stack;
	*stack = (*stack)->next;
	temp->next = (*stack)->next;
	(*stack)->next = temp;
	return (OK);
}

int	ps_swap(t_list **stack_a, t_list **stack_b, char which)
{
	if (which == WHICH_A)
		return (ps_s(stack_a));
	if (which == WHICH_B)
		return (ps_s(stack_a));
	ps_s(stack_a);
	ps_s(stack_b);
	return (OK);
}

int	ps_p(t_list **stack_to, t_list **stack_from)
{
	t_list	*temp;

	if (!stack_to || !stack_from || !*stack_from)
		return (ERR);
	temp = *stack_from;
	*stack_from = (*stack_from)->next;
	temp->next = NULL;
	ft_lstadd_front(stack_to, temp);
	return (OK);
}

int	ps_push(t_list **stack_a, t_list **stack_b, char which)
{
	if (which == WHICH_A)
		return (ps_p(stack_a, stack_b));
	return (ps_p(stack_b, stack_a));
}
