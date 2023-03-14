/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:35:06 by nroth             #+#    #+#             */
/*   Updated: 2023/02/14 12:35:08 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/* 
void	printeeer(char **cmd1, char **cmd2, char *infile_path, char *outfile_path)
{
	int	i;

	if (infile_path){
		ft_printf("infile: {%s}\n", infile_path);
	}
	if (outfile_path){
		ft_printf("outfile: {%s}\n", outfile_path);
	}
	if (cmd1)
	{
		ft_printf("\ncmd1:");
		i = 0;
		while (cmd1[i])
			ft_printf("%s, ", cmd1[i++]);
	}
	if (cmd2)
	{
		ft_printf("\ncmd2:");
		i = 0;
		while (cmd2[i])
			ft_printf("%s, ", cmd2[i++]);
	}
	ft_printf("\n-----------------------------------------\n\n");
}
 */

void	pipe_the_stuff(int argc, char *argv[], char *env[])
{
	int		file_fds[2];
	char	**cmds[2];
	int		i;
	int		stat;

	i = 2;
	while (i < argc - 1)
	{
		file_fds[0] = open(argv[1], O_RDONLY);
		file_fds[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
		if (file_fds[0] < 0)
			exit((perror(argv[1]), 1));
		if (file_fds[1] < 0)
			exit((perror(argv[argc - 1]), 1));
		cmds[0] = get_full_cmd(argv[i], env);
		if (i + 1 < argc - 1)
			cmds[1] = get_full_cmd(argv[i + 1], env);
		stat = piper(cmds, env, file_fds);
		release_cmds(cmds);
		dup2(file_fds[1], file_fds[0]);
		close(file_fds[0]);
		close(file_fds[1]);
		i += 2;
	}
	exit (stat);
}

int	main(int argc, char *argv[], char *env[])
{
	if (argc < 5)
	{
		ft_printf("Invalid number of arguments.\n");
		return (1);
	}
	pipe_the_stuff(argc, argv, env);
	return (0);
}
/*
	(void) argc;
	(void) argv;
	pipe_the_stuff(8,
		(char *[]) {"./pipex", "infile", "cat",
		 "cat", "cat", "cat", "wc -l", "out"}, env);
*/