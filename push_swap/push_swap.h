/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <nroth@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:21:56 by nroth             #+#    #+#             */
/*   Updated: 2023/02/27 18:12:29 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define MODE_PRNT		1
# define MODE_NOPRNT	0

# define WHICH_A		1
# define WHICH_B		2
# define WHICH_BOTH		3

# define TRUE			1
# define FALSE			0

# define ERR			-1
# define OK				0
# define WTF			-2

# define NRM  "\x1B[0m"
# define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define CYN  "\x1B[36m"
# define WHT  "\x1B[37m"

# include "Libft/libft.h"

// PUSHSWAP_FUNCS
int			ps_sa(t_list **stack_a, int mode);
int			ps_sb(t_list **stack_b, int mode);
int			ps_ss(t_list **stack_a, t_list **stack_b, int mode);

int			ps_pa(t_list **stack_a, t_list **stack_b, int mode);
int			ps_pb(t_list **stack_a, t_list **stack_b, int mode);
// PUSHSWAP_REDIR_FUNCS
int			ps_push(t_list **stack_a, t_list **stack_b, int mode, char which);
int			ps_swap(t_list **stack_a, t_list **stack_b, int mode, char which);

// ROT_FUNCS
int			ps_ra(t_list **stack_a, int mode);
int			ps_rb(t_list **stack_b, int mode);
int			ps_rr(t_list **stack_a, t_list **stack_b, int mode);
int			ps_rot(t_list **stack_a, t_list **stack_b, int mode, char which);

// REVROT_FUNCS
int			ps_rra(t_list **stack_a, int mode);
int			ps_rrb(t_list **stack_b, int mode);
int			ps_rrr(t_list **stack_a, t_list **stack_b, int mode);
int			ps_revrot(t_list **stack_a, t_list **stack_b, int mode, char which);

// DUMB SORTER
int			dumb_sort(t_list **lst_p);

// UTILS
int			lst_print(t_list *lst_a, t_list *lst_b);
t_list		*lst_from_arr(char *arr[]);
int			chek_if_lst_sorted(t_list *lst);

//UTILS2
int			get_val_index(t_list *bloc, t_list *lst);
void		get_val_to_top(t_list **stack, t_list *val, int which);
int			how_many_moves(t_list *stack_a, t_list *val);
int			get_val_at_index(t_list *list, int index);
int			print_stderr(char *str);

// UTILS3
t_list		*get_node_with_value(t_list *list, int val);
t_list		*lst_min_val(t_list	*list);
t_list		*lst_max_val(t_list	*list);
void		push_a_into_b(t_list **stack_a, t_list **stack_b);
void		push_b_into_a(t_list **stack_a, t_list **stack_b);

// UTILS4
void		*dup_num(void *num);
t_list		*get_top_chunk_val(t_list *lst, int min, int max);
t_list		*get_bottom_chunk_val(t_list *lst, int min, int max);
int			*get_chunks(t_list *stack_a, int *num_of_chunks);

//SORT 3_5
int			sort_three(t_list **stack_a);
int			sort_five(t_list **stack_a);
int			sort_alot(t_list **stack_a,
				t_list **stack_b, t_list *sorted_lst);
int			get_num_of_chunks(t_list *lst);

#endif