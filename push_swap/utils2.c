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

int	get_val_index( t_list *lst, t_list *node)
{
	int	i;

	i = 0;
	while (lst)
	{
		//ft_printf("cont: %i; node: %i\n", *((int *) lst->content),*((int *) node->content) );
		if (*((int *) lst->content) == *((int *) node->content))
			return (i);
		lst = lst->next;
		i++;
	}
	return (WTF);
}

/*
	count how many moves to get VAL to top
*/
int	how_many_moves(t_list *stack_a, t_list *val)
{
	int		index;
	int		alt_index;

	index = get_val_index(stack_a, val);
	alt_index = ft_lstsize(stack_a) - index;
	if (index > (ft_lstsize(stack_a) - index))
		return (ft_lstsize(stack_a) - index);
	else
		return (index);
}


void	get_val_pos_to_top(t_list **stack_a, t_list *val, int which)
{
	t_list	*lst;
	int		index;
	if (!stack_a || !*stack_a)
		return ;
	lst = *stack_a;
	lst_print(*stack_a, val);
	while (*((int *) lst->content) < *((int *) val->content))
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	index = get_val_index(lst, *stack_a);
	if (index < (ft_lstsize(*stack_a) - index))
	{
		while (*((int *)(*stack_a)->content) != *((int *) (lst)->content))
			ps_rot(stack_a, NULL, MODE_PRNT, which);
	}
	else
	{
		while (*((int *)(*stack_a)->content) != *((int *) (lst)->content))
			ps_revrot(stack_a, NULL, MODE_PRNT, which);
	}
}

void	get_val_to_top(t_list **stack, t_list *val, int which)
{
	int		index;

	if (!stack || !*stack)
		return ;
	index = get_val_index(*stack, val);
	if (index < 0)
		return ;
	if (index < (ft_lstsize(*stack) - index))
	{
		while (*((int *)(*stack)->content) != *((int *) (val)->content))
			ps_rot(stack, NULL, MODE_PRNT, which);
	}
	else
	{
		while (*((int *)(*stack)->content) != *((int *) (val)->content))
			ps_revrot(stack, NULL, MODE_PRNT, which);
	}
}

int	get_val_at_index(t_list *list, int index)
{
	int	i;

	i = 0;
	if (list < 0)
		return (WTF);
	while (i < index)
	{
		if (list == NULL)
			return (WTF);
		list = list->next;
		i++;
	}
	return (*((int *) list->content));
}

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
