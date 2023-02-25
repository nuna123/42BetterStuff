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

static int	nurse_infile(char **cmd, int pipees[2], int infile)
{
	pid_t	child;
	int		stat;

	stat = 0;
	child = fork();
	if (child == -1)
		return (-1);
	if (child == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(pipees[1], STDOUT_FILENO);
		close_pipes_files(pipees, infile, 0);
		execve(cmd[0], cmd, NULL);
		exit(127);
	}
	else
	{
		waitpid(child, &stat, 0);
		if (WEXITSTATUS(stat) == 127)
			ft_printf("%s./pipex: %s: command not found\n", RED, *cmd, NRM);

	}
	return (WEXITSTATUS(stat));
}

static int	nurse_outfile(char **cmd, int pipees[2], int outfile)
{
	pid_t	child;
	int		stat;

	stat = 0;
	child = fork();
	if (child == -1)
		return (-1);
	if (child == 0)
	{
		dup2(pipees[0], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close_pipes_files(pipees, 0, outfile);
		execve(cmd[0], cmd, NULL);
		exit(127);
	}
	else
	{
		close(pipees[1]);
		waitpid(child, &stat, 0);
		if (WEXITSTATUS(stat) == 127)
			ft_printf("%s./pipex: %s: command not found\n", RED, *cmd, NRM);
	}
	return (WEXITSTATUS(stat));
}

int	printerr(char *cmd, int err)
{
	ft_printf("\n%s./pipex: ", RED);
	if (cmd)
		ft_printf("%s: ",cmd);
	if (err == 127)
		err = 2;
	ft_printf("%s",strerror(err));
	ft_printf("%s\n", NRM);
	return (err);
}

int	piper(char **cmd1, char **cmd2, char *infile_path, char *outfile_path)
{
	int	infile_fd;
	int	outfile_fd;
	int	pipees[2];
	int	stat;

	infile_fd = open (infile_path, O_RDONLY);
	if (infile_fd < 0)
		return (-1);
	if (pipe(pipees) < 0)
		return (1);
	stat = nurse_infile(cmd1, pipees, infile_fd);
/* 	if (stat)
		return (printerr(*cmd1, stat)); */
	outfile_fd = open(outfile_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile_fd < 0)
		return (-1);
	stat = nurse_outfile(cmd2, pipees, outfile_fd);
	close_pipes_files(pipees, infile_fd, outfile_fd);
	while (wait(NULL) > -1)
		wait(NULL);
	return (stat);
}

/* 
int main(void)
{
	char* argv[] = {"/bin/cat", NULL};
	char* argv2[] = {"/usr/bin/grep", "piper", NULL};

	// char* argv[] = {"/usr/bin/cat", NULL};
	// char* argv2[] = {"/usr/bin/wc","-l",  NULL};
	int i = piper(argv, argv2, "infile","outfile");

	printf("ret: {%i}\n", i);
	return 0;
} */