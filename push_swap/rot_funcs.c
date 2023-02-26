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

#include "push_swap.h"

int	ps_ra(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("ra\n");
	(void) stack_b;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = NULL;
	ft_lstadd_back(stack_a, temp);
	return (OK);
}

int	ps_rb(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("rb\n");
	(void) stack_a;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = NULL;
	ft_lstadd_back(stack_b, temp);
	return (OK);
}

int	ps_rr(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return (ERR);
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("rr\n");
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = NULL;
	ft_lstadd_back(stack_b, temp);
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = NULL;
	ft_lstadd_back(stack_a, temp);
	return (OK);
}

int ps_rot(t_list **stack_a, t_list **stack_b, int mode, char which)
{
	if (which == WHICH_A)
		return (ps_ra(stack_a, stack_b, mode));
	if (which == WHICH_B)
		return (ps_rb(stack_a, stack_b, mode));
	return (ps_rr(stack_a, stack_b, mode));
}