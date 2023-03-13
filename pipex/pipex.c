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
void	printer(char **cmd1, char **cmd2, char *infile_path, char *outfile_path)
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


void pipe_the_stuff(int argc, char *argv[], char *env[])
{
	char	*infile_path;
	char	*outfile_path;
	char	**cmd1;
	char	**cmd2;
	int		i;

	infile_path = argv[1];
	outfile_path = argv[argc - 1];

	i = 1;
	while (++i < argc - 2)
	{
		cmd1 = get_full_cmd(argv[i], env);
		cmd2 = get_full_cmd(argv[i + 1], env);

		piper((char **[2]){cmd1, cmd2}, env, infile_path, outfile_path);
		release_cmds((char **[2]){cmd1, cmd2});
		infile_path = outfile_path;
	}
}


int	main(int argc, char *argv[], char *env[])
{

	// if (argc != 5)
	if (argc < 5)
	{
		ft_printf("Invalid number of arguments.\n");
		return (1);
	}
	pipe_the_stuff(argc, argv, env);
	return (0);
}
