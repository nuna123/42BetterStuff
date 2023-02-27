/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:04:50 by nroth             #+#    #+#             */
/*   Updated: 2023/02/27 18:12:19 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_val_index( t_list *lst, t_list *node)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (*((int *) lst->content) == *((int *) node->content))
			return (i);
		lst = lst->next;
		i++;
	}
	return (WTF);
}

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
		while (*((int *)(*stack)->content) != *((int *)(val)->content))
			ps_rot(stack, NULL, MODE_PRNT, which);
	}
	else
	{
		while (*((int *)(*stack)->content) != *((int *)(val)->content))
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

int	print_stderr(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERR);
}
