/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:04:50 by nroth             #+#    #+#             */
/*   Updated: 2023/02/22 20:04:52 by nroth            ###   ########.fr       */
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

//USED BY SORT100
void	push_into_b(t_list **stack_a, t_list **stack_b)
{
	t_list	*lst;
	t_list	*push_item;
	t_list	*next_down;

	lst = *stack_b;
	push_item = *stack_a;
	next_down = NULL;
	lst = *stack_b;
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
	ps_pb(stack_a, stack_b, MODE_PRNT);
}
