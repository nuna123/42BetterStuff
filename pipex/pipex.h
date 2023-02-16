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

# include "includes/libft.h"

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

// GET_FULL_NAME
char	*get_full_name(char *basename);
char	**get_full_cmd(char *cmd);

//PIPER
int		piper(char **cmd1, char **cmd2,
			char *infile_path, char *outfile_path);

//PIPEX_UTILS
void	*close_pipes_files(int pipees[2], int infile_fd, int outfile_fd);
void	*release_all(char **cmd1, char **cmd2,
			char *infile_path, char *outfile_path);

#endif
