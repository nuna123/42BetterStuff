/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:10:46 by nroth             #+#    #+#             */
/*   Updated: 2023/02/14 12:10:47 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
	births a child process which calls the 'which' command on the given string,
	and returns the allocated result.
*/
char	*get_full_name(char *basename)
{
	char	*fullname;
	char	*temp;
	int		pipees[2];
	int		stat;

	pipe(pipees);
	if (fork() == 0)
	{
		dup2(pipees[1], STDOUT_FILENO);
		close_pipes_files(pipees, 0, 0);
		if (execve("/usr/bin/which", (char *[3])
				{"/usr/bin/which", basename, NULL},
				(char *[3]){"HOME=/root", "PATH=/bin:/sbin", NULL }) == -1)
			exit(1);
	}
	wait(&stat);
	if (WEXITSTATUS(stat))
		return (NULL);
	dup2(pipees[0], STDIN_FILENO);
	temp = get_next_line(STDIN_FILENO);
	fullname = ft_strtrim(temp, "\n \t");
	free(temp);
	close_pipes_files(pipees, 0, 0);
	return (fullname);
}

char	**get_full_cmd(char *cmd)
{
	char	**ret;
	char	**added_ret;
	char	*fullname;
	int		ret_len;

	ret = ft_split(cmd, ' ');
	fullname = get_full_name(ret[0]);
	if (!ret || !fullname)
		return (NULL);
	ret_len = 0;
	while (ret[ret_len])
		ret_len++;
	added_ret = ft_calloc(ret_len + 1, sizeof(char *));
	if (!added_ret)
		return (release_all(ret, NULL, fullname, NULL));
	while (--ret_len >= 0)
		added_ret[ret_len] = ret[ret_len];
	free(added_ret[0]);
	added_ret[0] = ft_strdup(fullname);
	free(ret);
	return (added_ret);
}

/* 
int	main(int argc, char *argv[])
{
	char	*fullname;

	printf("MAIN PROGRAM\n");
	if (argc > 1)
		fullname = get_full_name(argv[1]);
	else
		fullname = get_full_name("ls");
	printf("FULLNAME: {%s}\n", fullname);
	free(fullname);
	return (0);
}
 */