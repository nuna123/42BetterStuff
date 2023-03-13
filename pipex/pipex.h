/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:50:06 by nroth             #+#    #+#             */
/*   Updated: 2023/02/15 16:50:08 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

//COLORS
# define NRM  "\x1B[0m"
# define RED  "\x1B[0m"
// # define RED  "\x1B[31m"
# define GRN  "\x1B[32m"
# define YEL  "\x1B[33m"
# define BLU  "\x1B[34m"
# define MAG  "\x1B[35m"
# define CYN  "\x1B[36m"
# define WHT  "\x1B[37m"

// GET_FULL_NAME
char	**get_full_cmd(char *cmd, char **env);

//PIPER
int		piper(char **cmds[2], char *env[],
			char *infile_path, char *outfile_path);

//PIPEX_UTILS
void	*close_pipes_files(int pipees[2], int infile_fd, int outfile_fd);
int		release_all(char **cmd1, char **cmd2,
			char *infile_path, char *outfile_path);

#endif
