/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:45:12 by nroth             #+#    #+#             */
/*   Updated: 2023/02/26 17:56:32 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"
#include <stdio.h>
#include <stdlib.h>

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

int	apply_rotate(t_list **stack_a, t_list **stack_b, char *action)
{
	if (ft_strlen(action) == 3)
	{
		if (ft_strncmp(action, "ra\n", 3) == 0)
			ps_rot(stack_a, stack_b, WHICH_A);
		else if (ft_strncmp(action, "rb\n", 3) == 0)
			ps_rot(stack_a, stack_b, WHICH_B);
		else if (ft_strncmp(action, "rr\n", 3) == 0)
			ps_rot(stack_a, stack_b, WHICH_BOTH);
		else
			return (ERR);
		return (OK);
	}
	else if (ft_strlen(action) == 4)
	{
		if (ft_strncmp(action, "rra\n", 4) == 0)
			ps_revrot(stack_a, stack_b, WHICH_A);
		else if (ft_strncmp(action, "rrb\n", 4) == 0)
			ps_revrot(stack_a, stack_b, WHICH_B);
		else if (ft_strncmp(action, "rrr\n", 4) == 0)
			ps_revrot(stack_a, stack_b, WHICH_BOTH);
		else
			return (ERR);
		return (OK);
	}
	return (ERR);
}

int	apply_action(t_list **stack_a, t_list **stack_b, char *action)
{
	if (action[0] == 's')
	{
		if (ft_strncmp(action, "sa\n", 3) == 0)
			ps_swap(stack_a, stack_b, WHICH_A);
		else if (ft_strncmp(action, "sb\n", 3) == 0)
			ps_swap(stack_a, stack_b, WHICH_B);
		else if (ft_strncmp(action, "ss\n", 3) == 0)
			ps_swap(stack_a, stack_b, WHICH_BOTH);
		else
			return (ERR);
		return (OK);
	}
	else if (action[0] == 'p')
	{
		if (ft_strncmp(action, "pa\n", 3) == 0)
			ps_push(stack_a, stack_b, WHICH_A);
		else if (ft_strncmp(action, "pb\n", 3) == 0)
			ps_push(stack_a, stack_b, WHICH_B);
		else
			return (ERR);
		return (OK);
	}
	else if (action[0] == 'r')
		return (apply_rotate(stack_a, stack_b, action));
	return (ERR);
}

int	main(int argc, char *argv[])
{
	t_list	*stacks[2];
	char	*buffer;
	int		lst_size;

	stacks[0] = NULL;
	stacks[1] = NULL;
	*buffer = '!';
	if (argc == 2)
		stacks[0] = lst_from_str(argv[1]);
	else if (argc > 1)
		stacks[0] = lst_from_arr(&argv[1]);
	if (!stacks[0])
	{
		//ft_printf("some err in stacks creation :(\n");
		ft_lstclear(&stacks[0], free);
		return (print_stderr("Error\n"));
	}
	lst_size = ft_lstsize(stacks[0]);
	while (buffer)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (apply_action(&stacks[0], &stacks[1], buffer) != OK)
			return (print_stderr("Error\n"));
		free(buffer);
	}
	free(buffer);
	return (chek_if_lst_sorted(stacks[0], lst_size));
}
