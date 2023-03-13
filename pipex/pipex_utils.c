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

int	release_all(char **cmd1, char **cmd2,
			char *infile_path, char *outfile_path)
{
	int	i;

	if (cmd1)
	{
		i = -1;
		while (cmd1[++i])
			free(cmd1[i]);
		free(cmd1[i]);
		free(cmd1);
	}
	if (cmd2)
	{
		i = -1;
		while (cmd2[++i])
			free(cmd2[i]);
		free(cmd2[i]);
		free(cmd2);
	}
	if (infile_path)
		free(infile_path);
	if (outfile_path)
		free(outfile_path);
	return (1);
}

int	release_cmds(char **cmds[2])
{
	int	i;

	if (cmds[0])
	{
		i = -1;
		while (cmds[0][++i])
			free(cmds[0][i]);
		free(cmds[0][i]);
		free(cmds[0]);
	}
	if (cmds[1])
	{
		i = -1;
		while (cmds[1][++i])
			free(cmds[1][i]);
		free(cmds[1][i]);
		free(cmds[1]);
	}
	return (1);
}
