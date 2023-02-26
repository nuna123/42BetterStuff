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

static t_list	*find_bef_last(t_list *lst)
{
	if (!lst || !lst->next)
		return (NULL);
	while (lst->next->next)
		lst = lst->next;
	return (lst);
}

int	ps_rra(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("rra\n");
	(void) stack_b;
	temp = ft_lstlast(*stack_a);
	find_bef_last(*stack_a)->next = NULL;
	ft_lstadd_front(stack_a, temp);
	temp = ft_lstlast(*stack_a);
	temp->next = NULL;
	return (OK);
}

int	ps_rrb(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("rrb\n");
	(void) stack_a;
	temp = ft_lstlast(*stack_b);
	find_bef_last(*stack_b)->next = NULL;
	ft_lstadd_front(stack_b, temp);
	temp = ft_lstlast(*stack_b);
	temp->next = NULL;
	return (OK);
}

int	ps_rrr(t_list **stack_a, t_list **stack_b, int mode)
{
	t_list	*temp;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return (ERR);
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return (ERR);
	if (mode == MODE_PRNT)
		ft_printf("rr\n");
	temp = ft_lstlast(*stack_a);
	find_bef_last(*stack_a)->next = NULL;
	ft_lstadd_front(stack_a, temp);
	temp = ft_lstlast(*stack_a);
	temp->next = NULL;
	temp = ft_lstlast(*stack_b);
	find_bef_last(*stack_b)->next = NULL;
	ft_lstadd_front(stack_b, temp);
	temp = ft_lstlast(*stack_b);
	temp->next = NULL;
	return (OK);
}

int ps_revrot(t_list **stack_a, t_list **stack_b, int mode, char which)
{
	if (which == WHICH_A)
		return (ps_rra(stack_a, stack_b, mode));
	if (which == WHICH_B)
		return (ps_rrb(stack_a, stack_b, mode));
	return (ps_rrr(stack_a, stack_b, mode));
}