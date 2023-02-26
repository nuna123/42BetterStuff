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

int	ps_sa(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("sa\n");
	(void) stack_b;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = (*stack_a)->next;
	(*stack_a)->next = temp;
	return (OK);
}

int	ps_sb(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("sb\n");
	(void) stack_a;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = (*stack_b)->next;
	(*stack_b)->next = temp;
	return (OK);
}

int	ps_ss(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return (ERR);
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("ss\n");
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = (*stack_a)->next;
	(*stack_a)->next = temp;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = (*stack_b)->next;
	(*stack_b)->next = temp;
	return (OK);
}

int	ps_pa(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_a || !stack_b || !*stack_b)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("pa\n");
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = NULL;
	ft_lstadd_front(stack_a, temp);
	return (OK);
}

int	ps_pb(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_b || !stack_a || !*stack_a)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("pb\n");
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = NULL;
	ft_lstadd_front(stack_b, temp);
	return (OK);
}


