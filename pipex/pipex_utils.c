/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:48:27 by nroth             #+#    #+#             */
/*   Updated: 2023/02/15 16:48:28 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(void **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	release_cmds(char **cmds[2])
{
	if (cmds[0])
		free_arr((void **) cmds[0]);
	if (cmds[1])
		free_arr((void **) cmds[1]);
	return (1);
}
