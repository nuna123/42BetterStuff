/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:04:50 by nroth             #+#    #+#             */
/*   Updated: 2023/02/27 13:55:35 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	chek_if_lst_sorted(t_list *lst_a, t_list *lst_b, int lst_size)
{
	t_list	*lst;

	if (!lst_a || ft_lstsize(lst_a) != lst_size)
	{
		ft_lstclear(&lst_a, free);
		ft_lstclear(&lst_b, free);
		return (ft_printf("KO\n") - 2);
	}
	lst = lst_a;
	while (lst)
	{
		if (!lst->next)
		{
			ft_lstclear(&lst_a, free);
			return (ft_printf("OK\n") - 3);
		}
		if (*((int *)lst->content) > *((int *)lst->next->content))
		{
			ft_lstclear(&lst_a, free);
			return (ft_printf("KO\n") - 2);
		}
		lst = lst->next;
	}
	ft_lstclear(&lst_a, free);
	return (ft_printf("OK\n") - 2);
}

static int	str_isvalid(char *s)
{
	int	sign;

	sign = 1;
	if (*s == '-' || *s == '+')
	{
		sign = 44 - *s;
		s++;
	}
	if (ft_strlen(s) > 10)
		return (FALSE);
	if (ft_strlen(s) == 10 && sign > 0 && ft_strncmp(s, "2147483647", 10) > 0)
		return (FALSE);
	if (ft_strlen(s) == 10 && sign < 0 && ft_strncmp(s, "2147483648", 10) > 0)
		return (FALSE);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (FALSE);
		s++;
	}
	return (TRUE);
}

static int	val_in_lst(int val, t_list *lst)
{
	while (lst)
	{
		if (*((int *)lst->content) == val)
			return (TRUE);
		lst = lst->next;
	}
	return (FALSE);
}

t_list	*lst_from_arr(char *arr[])
{
	t_list	*lst;
	int		i;
	int		*num;

	i = 0;
	lst = NULL;
	while (arr[i])
	{
		if (!str_isvalid(arr[i]) || val_in_lst(ft_atoi(arr[i]), lst))
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		num = malloc(sizeof(int));
		if (!num)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		*num = ft_atoi(arr[i]);
		ft_lstadd_back(&lst, ft_lstnew(num));
		i++;
	}
	return (lst);
}

int	print_stderr(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (ERR);
}

/* 
int	lst_print(t_list *lst_a, t_list *lst_b)
{
	ft_printf("-----------------\n");
	while (lst_a || lst_b)
	{
		if (lst_a)
			ft_printf("  %-10i", (*(int *) lst_a->content));
		else
			ft_printf("%12s", "");
		if (lst_b)
			ft_printf("%-10i\n", (*(int *) lst_b->content));
		else
			ft_printf("\n");
		if (lst_a)
			lst_a = lst_a->next;
		if (lst_b)
			lst_b = lst_b->next;
	}
	ft_printf("-----------------\n");
	ft_printf("  %s\t    %s  \n", "a", "b");
	ft_printf("-----------------\n\n");
	return (OK);
}
 */