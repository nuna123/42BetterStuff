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

void	*dup_num(void *num)
{
	int	*new_num;

	new_num = malloc(sizeof(int));
	*new_num = *((int *) num);
	return ((void *) new_num);
}

t_list	*get_top_chunk_val(t_list *lst, int min, int max)
{
	while (lst)
	{
		if (*((int *) lst->content) >= min
			&& *((int *) lst->content) < max)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_list	*get_bottom_chunk_val(t_list *lst, int min, int max)
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
	return (NULL);
}

int	*get_chunks(t_list *stack_a, int *num_of_chunks)
{
	int	chunk_size;
	int	i;
	int	*chunks;

	*num_of_chunks = get_num_of_chunks(stack_a);
	chunks = ft_calloc(*num_of_chunks, sizeof(int));
	chunk_size = ft_lstsize(stack_a) / (*num_of_chunks - 1);
	i = 0;
	chunks[0] = get_val_at_index(stack_a, 0);
	while (++i < (*num_of_chunks - 1))
		chunks[i] = get_val_at_index(stack_a, chunk_size * i);
	chunks[*num_of_chunks - 1] = get_val_at_index(stack_a,
			ft_lstsize(stack_a) - 1);
	return (chunks);
}
