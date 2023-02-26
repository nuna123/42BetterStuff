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

int	ps_r(t_list **stack)
{
	t_list	*temp;

	if (!stack || !*stack || !(*stack)->next)
		return (ERR);
	temp = *stack;
	*stack = (*stack)->next;
	temp->next = NULL;
	ft_lstadd_back(stack, temp);
	return (OK);
}

int	ps_rot(t_list **stack_a, t_list **stack_b, char which)
{
	if (which == WHICH_A)
		return (ps_r(stack_a));
	if (which == WHICH_B)
		return (ps_r(stack_b));
	ps_r(stack_a);
	ps_r(stack_b);
	return (OK);
}

static t_list	*find_bef_last(t_list *lst)
{
	if (!lst || !lst->next)
		return (NULL);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}

int	ps_rr(t_list **stack)
{
	t_list	*temp;

	if (!stack || !*stack || !(*stack)->next)
		return (ERR);
	temp = ft_lstlast(*stack);
	find_bef_last(*stack)->next = NULL;
	ft_lstadd_front(stack, temp);
	temp = ft_lstlast(*stack);
	temp->next = NULL;
	return (OK);
}

int	ps_revrot(t_list **stack_a, t_list **stack_b, char which)
{
	if (which == WHICH_A)
		return (ps_rr(stack_a));
	if (which == WHICH_B)
		return (ps_rr(stack_a));
	ps_rr(stack_a);
	ps_rr(stack_b);
	return (OK);
}
