/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:04:50 by nroth             #+#    #+#             */
/*   Updated: 2023/02/27 15:49:00 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*get_node_with_value(t_list *list, int val)
{
	if (!list)
		return (NULL);
	while (list)
	{
		if (*((int *) list->content) == val)
			return (list);
		list = list->next;
	}
	return (NULL);
}

t_list	*lst_max_val(t_list	*list)
{
	t_list	*max;

	max = list;
	while (list)
	{
		if (*((int *) max->content) < *((int *) list->content))
			max = list;
		list = list->next;
	}
	return (max);
}

t_list	*lst_min_val(t_list	*list)
{
	t_list	*min;

	min = list;
	while (list)
	{
		if (*((int *) min->content) > *((int *) list->content))
			min = list;
		list = list->next;
	}
	return (min);
}

//USED BY SORT100, which === which to push into
// void	push_into_b(t_list **stack_a, t_list **stack_b)
void	push_a_into_b(t_list **stack_a, t_list **stack_b)
{
	t_list	*lst;
	t_list	*push_item;
	t_list	*next_down;

	lst = *stack_b;
	push_item = *stack_a;
	next_down = NULL;
	while (lst)
	{
		if (*((int *) lst->content) < *((int *) push_item->content))
		{
			if (!next_down || *((int *) next_down->content)
				< *((int *) lst->content))
				next_down = lst;
		}
		lst = lst->next;
	}
	if (!next_down)
		next_down = lst_max_val(*stack_b);
	get_val_to_top(stack_b, next_down, WHICH_B);
	ps_push(stack_a, stack_b, MODE_PRNT, WHICH_B);
}

void	push_b_into_a(t_list **stack_a, t_list **stack_b)
{
	t_list	*lst;
	t_list	*push_item;
	t_list	*next_down;

	lst = *stack_a;
	push_item = *stack_b;
	next_down = NULL;
	while (lst)
	{
		if (*((int *) lst->content) > *((int *) push_item->content))
		{
			if (!next_down || *((int *) next_down->content)
				> *((int *) lst->content))
				next_down = lst;
		}
		lst = lst->next;
	}
	if (!next_down)
		next_down = lst_min_val(*stack_a);
	get_val_to_top(stack_a, next_down, WHICH_A);
	ps_push(stack_a, stack_b, MODE_PRNT, WHICH_A);
}
