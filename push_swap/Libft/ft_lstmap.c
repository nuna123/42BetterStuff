/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:38:44 by nroth             #+#    #+#             */
/*   Updated: 2023/01/14 16:38:46 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*lst_item;
	void	*content;

	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		lst_item = ft_lstnew(content);
		if (!lst_item)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, lst_item);
		if (!lst_item)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (new_lst);
}
