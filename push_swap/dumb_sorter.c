/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumb_sorter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:24:56 by nroth             #+#    #+#             */
/*   Updated: 2023/02/23 11:24:58 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	dumb_sort_expander(t_list **lst_p, t_list **lst, t_list	**prev_item)
{
	if (!*prev_item)
		*lst_p = (*lst)->next;
	else
		(*prev_item)->next = (*lst)->next;
	ps_sa(lst, NULL, MODE_NOPRNT);
}

int	dumb_sort(t_list **lst_p)
{
	t_list	*lst;
	t_list	*prev_item;

	if (!lst_p || !*lst_p)
		return (WTF);
	lst = *lst_p;
	prev_item = NULL;
	while (chek_if_lst_sorted(*lst_p) == FALSE)
	{
		if (!lst->content || !lst->next)
		{
			lst = *lst_p;
			prev_item = NULL;
		}
		if (*((int *) lst->content) > *((int *) lst->next->content))
			dumb_sort_expander(lst_p, &lst, &prev_item);
		prev_item = lst;
		lst = lst->next;
	}
	return (OK);
}
