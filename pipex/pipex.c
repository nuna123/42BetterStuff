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

void	printer(char **cmd1, char **cmd2, char *infile_path, char *outfile_path)
{
	int	i;

	ft_printf("infile: {%s}\n", infile_path);
	ft_printf("outfile: {%s}\n", outfile_path);
	ft_printf("\ncmd1:");
	i = 0;
	while (cmd1[i])
		ft_printf("%s, ", cmd1[i++]);
	ft_printf("\ncmd2:");
	i = 0;
	while (cmd2[i])
		ft_printf("%s, ", cmd2[i++]);
}

int	main(int argc, char *argv[])
{
	char	*infile_path;
	char	*outfile_path;
	char	**cmd1;
	char	**cmd2;

	if (argc != 5)
	{
		infile_path = ft_strdup("infile");
		outfile_path = ft_strdup("outfile");
		cmd1 = get_full_cmd("cat");
		cmd2 = get_full_cmd("grep asdf");
	}
	else
	{
		infile_path = ft_strdup(argv[1]);
		outfile_path = ft_strdup(argv[4]);
		cmd1 = get_full_cmd(argv[2]);
		cmd2 = get_full_cmd(argv[3]);
	}
	printer(cmd1, cmd2, infile_path, outfile_path);
	piper(cmd1, cmd2, infile_path, outfile_path);
	release_all(cmd1, cmd2, infile_path, outfile_path);
	return (0);
}
