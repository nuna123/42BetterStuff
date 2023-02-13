#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char	*get_name(char *basename);

#endif