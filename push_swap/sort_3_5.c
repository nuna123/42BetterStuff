/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:20:30 by nroth             #+#    #+#             */
/*   Updated: 2023/02/23 12:09:40 by nroth            ###   ########.fr       */
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
			ps_sa(stack_a, NULL, MODE_PRNT);
		else if (*((int *) lst->content) < *((int *)lst->next->content)
			&& *((int *)lst->content) > *((int *)lst->next->next->content))
			ps_rra(stack_a, NULL, MODE_PRNT);
		else if (*((int *)lst->content) > *((int *)lst->next->content)
			&& *((int *)lst->content) > *((int *)lst->next->next->content))
			ps_ra(stack_a, NULL, MODE_PRNT);
		else
			ps_sa(stack_a, NULL, MODE_PRNT);
	}
	return (chek_if_lst_sorted(*stack_a));
}

int	sort_five(t_list **stack_a, t_list **stack_b)
{
	if (chek_if_lst_sorted(*stack_a) != TRUE)
	{
		ps_pb(stack_a, stack_b, MODE_PRNT);
		ps_pb(stack_a, stack_b, MODE_PRNT);
		sort_three(stack_a);
		sort_three(stack_b);
		while (*stack_b)
		{
			get_val_pos_to_top(stack_a, *stack_b, WHICH_A);
			ps_pa(stack_a, stack_b, MODE_PRNT);
		}
		while (*((int *)(*stack_a)->content) >
				*((int *)(*stack_a)->next->content))
			ps_ra(stack_a, stack_b, MODE_PRNT);
	}
	return (chek_if_lst_sorted(*stack_a));
}

void	get_chunks(t_list *stack_a, int chunks[5])
{
	int	chunk_size;
	int	i;

	chunk_size = ft_lstsize(stack_a) / 5;
	i = 0;
	chunks[0] = get_val_at_index(stack_a, 0);
	while (++i < 5)
		chunks[i] = get_val_at_index(stack_a, chunk_size * i);
	chunks[5] = get_val_at_index(stack_a, ft_lstsize(stack_a) - 1);
}

t_list *get_top_chunk_val(t_list *lst, int min, int max)
{
	while (lst)
	{
		if (*((int *) lst->content) >= min
			&& *((int *) lst->content) < max)
			return(lst);
		lst = lst->next;
	}
	return(NULL);
}
t_list *get_bottom_chunk_val(t_list *lst, int min, int max)
{
	t_list	*ret;

	while (lst)
	{
		if (*((int *) lst->content) >= min
			&& *((int *) lst->content) < max)
			ret = lst;
		lst = lst->next;
	}
	if (ret)
		return (ret);
	return(NULL);
}


void	reset_chunk(t_list **stack_b, t_list *sorted_lst, int chunks[], int i)
{
	t_list	*node;

	node = get_node_with_value(sorted_lst, chunks[i]);
	//node = node->next;
	get_val_to_top(stack_b, node, WHICH_B);
}


void	push_into_b(t_list **stack_a, t_list **stack_b)
{
	//get next largest item in list, if the value is largest in list get smallest in list
	t_list	*lst;
	t_list	*temp_item;

	lst = *stack_b;
	temp_item = NULL;
	while (lst)
	{
		if(*((int *)lst->content) > *((int *) (*stack_a)->content))// if is larger, 
		{
			if(temp_item && *((int *)lst->content) < *((int *) temp_item->content))
				temp_item = lst;
		}
		lst = lst->next;
	}
	if (!temp_item)
		temp_item = *stack_b;
	get_val_to_top(stack_b, temp_item, WHICH_B);
	ps_push(stack_a, stack_b, MODE_PRNT, WHICH_B);
}

int	sort_hundred(t_list **stack_a, t_list **stack_b, t_list *sorted_lst)
{
	int	chunks[6];
	int	i;
	t_list	*top_val;
	t_list	*butt_val;
	
	get_chunks(sorted_lst, chunks);
	i = 1;

	if (chek_if_lst_sorted(*stack_a) != FALSE)
		return (chek_if_lst_sorted(*stack_a));
	while (i <= 5)
	{
		//lst_print(*stack_a, *stack_b);
		while (get_top_chunk_val(*stack_a, chunks[i - 1], chunks[i]))
		{
			top_val = get_top_chunk_val(*stack_a, chunks[i - 1], chunks[i]);
			butt_val = get_bottom_chunk_val(*stack_a, chunks[i - 1], chunks[i]);
			printf("topval: %i; buttval: %i\n", *((int *) top_val->content), *((int *) butt_val->content));
			if(top_val)
			{
				if (how_many_moves(*stack_a, top_val) < how_many_moves(*stack_a, butt_val))
				{
					get_val_to_top(stack_a, top_val, WHICH_A);
					get_val_pos_to_top(stack_b, top_val, WHICH_B);
					lst_print(*stack_a, *stack_b);
				}
				else
				{
					get_val_to_top(stack_a, butt_val, WHICH_A);
					get_val_pos_to_top(stack_b, butt_val, WHICH_B);
					lst_print(*stack_a, *stack_b);
				}

				//get_val_pos_to_top(stack_b, );
				//ps_pa(stack_a, stack_b, MODE_PRNT);
				//ps_pb(stack_a, stack_b, MODE_PRNT);
				push_into_b(stack_a, stack_b);
			}
		}
		reset_chunk(stack_b, sorted_lst, chunks, i);
		//get_val_to_top(stack_b, get_node_with_value(*stack_b, ));
		i++;
	}
	while (*stack_b)
		ps_pa(stack_a, stack_b, MODE_PRNT);
	//lst_print(*stack_a, *stack_b);
	
	return(OK);
}