/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:20:30 by nroth             #+#    #+#             */
/*   Updated: 2023/02/27 18:13:07 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*lst_from_str(char *str)
{
	t_list	*lst_a;
	char	**arr;
	int		i;

	arr = ft_split(str, ' ');
	lst_a = lst_from_arr(arr);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (lst_a);
}

void	sort_stuff(t_list **lst_a)
{
	t_list	*sorted_lst;
	t_list	*lst_b;

	lst_b = NULL;
	sorted_lst = ft_lstmap(*lst_a, dup_num, free);
	dumb_sort(&sorted_lst);
	if (ft_lstsize(*lst_a) <= 3)
		sort_three(lst_a);
	else if (ft_lstsize(*lst_a) <= 5)
		sort_five(lst_a);
	else
		sort_alot(lst_a, &lst_b, sorted_lst);
	ft_lstclear(&sorted_lst, free);
}

int	main(int argc, char *argv[])
{
	t_list	*lst_a;

	lst_a = NULL;
	if (argc == 2)
		lst_a = lst_from_str(argv[1]);
	else if (argc > 1)
		lst_a = lst_from_arr(&argv[1]);
	else
		return (print_stderr("Error\n"));
	if (!lst_a)
	{
		ft_lstclear(&lst_a, free);
		return (print_stderr("Error\n"));
	}
	sort_stuff(&lst_a);
	ft_lstclear(&lst_a, free);
	return (OK);
}
