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

static void	piper_extand(int pipees[2], char *outfile_path,
						char **cmds[2], char *env[])
{
	int	file_fd;

	close(pipees[1]);
	file_fd = open(outfile_path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (file_fd == -1)
		perror(outfile_path);
	dup2(pipees[0], STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	execve(cmds[1][0], cmds[1], env);
	write(STDERR_FILENO, "pipex: ", 7);
	write(STDERR_FILENO, cmds[1][0], ft_strlen(cmds[1][0]));
	write(STDERR_FILENO, ": command not found\n", 20);
	release_all(cmds[0], cmds[1], NULL, NULL);
	exit(127);
}

static void	forker(int pipees[2], int file_fd,
				char **cmds[2], char *env[])
{
	close (pipees[0]);
	dup2(file_fd, STDIN_FILENO);
	dup2(pipees[1], STDOUT_FILENO);
	close (file_fd);
	close (pipees[1]);
	execve(cmds[0][0], cmds[0], env);
	release_all(cmds[0], cmds[1], NULL, NULL);
	exit(127);
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
	{
		perror(infile_path);
		return (release_all(cmds[0], cmds[1], NULL, NULL));
	}
	child = fork();
	if (child == 0)
		forker(pipees, file_fd, cmds, env);
	waitpid(child, &stat, 0);
	if (WEXITSTATUS(stat) == 127)
		ft_printf("pipex: %s: %s\n", cmds[0][0], "command not found");
	else if (WEXITSTATUS(stat))
		perror("pipex");
	close(file_fd);
	piper_extand(pipees, outfile_path, cmds, env);
	return (0);
}

/* 
#include "pipex.h"

static void	piper_extand(int pipees[2], char *outfile_path,
						char **cmd2, char *env[])
{
	int	file_fd;

	close(pipees[1]);
	file_fd = open(outfile_path, O_CREAT | O_WRONLY | O_TRUNC);
	if (file_fd == -1)
		perror(outfile_path);
	dup2(pipees[0], STDIN_FILENO);
	dup2(file_fd, STDOUT_FILENO);
	execve(cmd2[0], cmd2, env);
	ft_printf("pipex: %s: %s\n", cmd2[0], "command not found");
	exit(127);
}

void	forker(int pipees[2], int file_fd,
				char **cmd1, char *env[])
{
	close (pipees[0]);
	dup2(file_fd, STDIN_FILENO);
	dup2(pipees[1], STDOUT_FILENO);
	close (file_fd);
	close (pipees[1]);
	execve(cmd1[0], cmd1, env);
	exit(127);
}

int	piper(char **cmd1, char **cmd2, char *env[],
		char *infile_path, char *outfile_path)
{
	int		file_fd;
	pid_t	child;
	int		pipees[2];
	int		stat;


	file_fd = open(infile_path, O_RDONLY);
	if (file_fd == -1 || pipe(pipees) != 0)
	{
		perror(infile_path);
		return (release_all(cmd1, cmd2, NULL, NULL));
	}
	child = fork();
	if(child == 0)
		forker(pipees, file_fd, cmd1, env);
	waitpid(child, &stat, 0);
	if(WEXITSTATUS(stat) == 127)
		ft_printf("pipex: %s: %s\n", cmd1[0], "command not found");
	else if(WEXITSTATUS(stat))
		perror("pipex");
	close(file_fd);
	piper_extand(pipees, outfile_path, cmd2, env);
	return (0);
}
 */