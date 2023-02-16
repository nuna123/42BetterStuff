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

void	*close_pipes_files(int pipees[2], int infile_fd, int outfile_fd)
{
	close(pipees[0]);
	close(pipees[1]);
	if (infile_fd)
		close(infile_fd);
	if (outfile_fd)
		close (outfile_fd);
	return (NULL);
}

void	*release_all(char **cmd1, char **cmd2,
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
		free(cmd2);
	}
	if (infile_path)
		free(infile_path);
	if (outfile_path)
		free(outfile_path);
	return (NULL);
}
