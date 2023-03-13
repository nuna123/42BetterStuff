/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:03:24 by nroth             #+#    #+#             */
/*   Updated: 2023/02/14 15:03:26 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	forker(int pipees[2], int file_fd,
				char **cmds[2], char *env[])
{
	close (pipees[0]);
	dup2(file_fd, STDIN_FILENO);
	dup2(pipees[1], STDOUT_FILENO);
	close (file_fd);
	close (pipees[1]);
	execve(cmds[0][0], cmds[0], env);
	release_cmds(cmds);
	exit(127);
}

static void	forker2(int pipees[2], int file_fd,
				char **cmds[2], char *env[])
{
	close (pipees[1]);
	dup2(pipees[0], STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	close (file_fd);
	close (pipees[0]);
	execve(cmds[1][0], cmds[1], env);
	release_cmds(cmds);
	exit(127);
}

static int	wait_for_child(char **cmd, pid_t child)
{
	int		stat;

	waitpid(child, &stat, 0);
	if (WEXITSTATUS(stat) == 127)
		ft_printf("pipex: %s: %s\n", cmd[0], "command not found");
	else if (WEXITSTATUS(stat))
		perror("pipex");
	return (WEXITSTATUS(stat));
}

int	piper(char **cmds[2], char *env[],
		char *infile_path, char *outfile_path)
{
	int		file_fd;
	pid_t	child;
	int		pipees[2];
	int		stat;

	file_fd = open(infile_path, O_RDONLY);
	if (file_fd == -1 || pipe(pipees) != 0)
		return (perror(infile_path), 1);
	child = fork();
	if (child == 0)
		forker(pipees, file_fd, cmds, env);
	wait_for_child(cmds[0], child);
	close(file_fd);
	close(pipees[1]);
	file_fd = open(outfile_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (file_fd == -1)
		perror(outfile_path);
	child = fork();
	if (child == 0)
		forker2(pipees, file_fd, cmds, env);
	stat = wait_for_child(cmds[1], child);
	return (stat);
}
