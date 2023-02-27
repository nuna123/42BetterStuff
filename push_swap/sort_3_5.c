/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:20:30 by nroth             #+#    #+#             */
/*   Updated: 2023/02/27 17:45:16 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	POSSIBLE CASES FOR 3 ITEMS:
		1		1		2		2		3		3
		2		3		1		3		1		2
		3		2		3		1		2		1
	  NONE		SA		SA		RRA		RA		SA
	  			RA								RRA
 */

int	sort_three(t_list **stack_a)
{
	t_list	*lst;

	while (chek_if_lst_sorted(*stack_a) == FALSE)
	{
		lst = *stack_a;
		if (ft_lstsize(*stack_a) == 2)
			ps_sa(stack_a, MODE_PRNT);
		else if (*((int *) lst->content) < *((int *)lst->next->content)
			&& *((int *)lst->content) > *((int *)lst->next->next->content))
			ps_rra(stack_a, MODE_PRNT);
		else if (*((int *)lst->content) > *((int *)lst->next->content)
			&& *((int *)lst->content) > *((int *)lst->next->next->content))
			ps_ra(stack_a, MODE_PRNT);
		else
			ps_sa(stack_a, MODE_PRNT);
	}
	return (chek_if_lst_sorted(*stack_a));
}

int	sort_five(t_list **stack_a)
{
	t_list	*stack_b;

	stack_b = NULL;
	if (chek_if_lst_sorted(*stack_a) != TRUE)
	{
		ps_pb(stack_a, &stack_b, MODE_PRNT);
		ps_pb(stack_a, &stack_b, MODE_PRNT);
		sort_three(stack_a);
		while (stack_b)
			push_b_into_a(stack_a, &stack_b);
		get_val_to_top(stack_a, lst_min_val(*stack_a), WHICH_A);
	}
	return (chek_if_lst_sorted(*stack_a));
}

static void	sort_hun_extand(t_list **stack_a, t_list **stack_b,
					t_list *top_val, t_list *butt_val)
{
	if (top_val)
	{
		if (how_many_moves(*stack_a, top_val)
			< how_many_moves(*stack_a, butt_val))
			get_val_to_top(stack_a, top_val, WHICH_A);
		else
			get_val_to_top(stack_a, butt_val, WHICH_A);
		push_a_into_b(stack_a, stack_b);
	}
}

int	get_num_of_chunks(t_list *lst)
{
	int	num_of_chunks;

	num_of_chunks = ft_lstsize(lst) / 20 + 1;
	if (num_of_chunks == 1)
		num_of_chunks = 2;
	return (num_of_chunks);
}

int	sort_alot(t_list **stack_a, t_list **stack_b, t_list *sorted_lst)
{
	int		*chunks;
	int		num_of_chunks;
	int		i;
	t_list	*top_val;
	t_list	*butt_val;

	i = 1;
	if (chek_if_lst_sorted(*stack_a) != FALSE)
		return (chek_if_lst_sorted(*stack_a));
	chunks = get_chunks(sorted_lst, &num_of_chunks);
	while (i < num_of_chunks)
	{
		while (get_top_chunk_val(*stack_a, chunks[i - 1], chunks[i]))
		{
			top_val = get_top_chunk_val(*stack_a, chunks[i - 1], chunks[i]);
			butt_val = get_bottom_chunk_val(*stack_a, chunks[i - 1], chunks[i]);
			sort_hun_extand(stack_a, stack_b, top_val, butt_val);
		}
		get_val_to_top(stack_b, lst_max_val(*stack_b), WHICH_B);
		i++;
	}
	while (*stack_b)
		ps_pa(stack_a, stack_b, MODE_PRNT);
	free(chunks);
	return (OK);
}
