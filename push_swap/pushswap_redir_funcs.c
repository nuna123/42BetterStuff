/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_fileA.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:20:30 by nroth             #+#    #+#             */
/*   Updated: 2023/02/21 11:20:31 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ps_swap(t_list **stack_a, t_list **stack_b, int mode, char which)
{
	if (which == WHICH_A)
		return (ps_sa(stack_a, mode));
	if (which == WHICH_B)
		return (ps_sb(stack_a, mode));
	return (ps_ss(stack_a, stack_b, mode));
}

int	ps_push(t_list **stack_a, t_list **stack_b, int mode, char which)
{
	if (which == WHICH_A)
		return (ps_pa(stack_a, stack_b, mode));
	return (ps_pb(stack_a, stack_b, mode));
}
