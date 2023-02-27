/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:56 by nroth             #+#    #+#             */
/*   Updated: 2023/02/27 18:03:32 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "Libft/libft.h"

# define WHICH_A		1
# define WHICH_B		2
# define WHICH_BOTH		3

# define ERR			-1
# define OK				0
# define WTF			-2

# define TRUE			1
# define FALSE			0

int		ps_s(t_list **stack);
int		ps_swap(t_list **stack_a, t_list **stack_b, char which);
int		ps_p(t_list **stack_to, t_list **stack_from);
int		ps_push(t_list **stack_a, t_list **stack_b, char which);
int		free_and_leave(t_list *stacks[2]);

int		ps_r(t_list **stack);
int		ps_rot(t_list **stack_a, t_list **stack_b, char which);
int		ps_rr(t_list **stack);
int		ps_revrot(t_list **stack_a, t_list **stack_b, char which);

int		chek_if_lst_sorted(t_list *lst_a, t_list *lst_b, int lst_size);
t_list	*lst_from_arr(char *arr[]);
int		print_stderr(char *str);

#endif