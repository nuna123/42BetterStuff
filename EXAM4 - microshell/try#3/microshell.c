#include "./microshell.h"

void print_err (char *str, char *arg)
{
	while (str && *str)
	{
		if (*str == '%')
		{
			while (arg && *arg)
				write(STDERR_FILENO, arg++, 1);
		}
		else
			write(STDERR_FILENO, str, 1);
		str++;
	}
}

/*
pid_t	fake_fork (void)
	{return -1;}
*/

int	exec_cmd(int in_fd, char **argv,char **envp)
{

		dup2(in_fd, STDIN_FILENO);
		close (in_fd);
		execve (argv[0], argv, envp);
		print_err("error: cannot execute %\n", argv[0]);
		return (errno);
}

int main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return 1;

	int cmd_len;
	int in_fd;
	int pipes[2];


	in_fd = dup(STDIN_FILENO);

	if (in_fd == -1)
		exit ((close(in_fd),
			print_err("error: fatal\n", NULL), errno));

	argv++;
	while (argv && *argv)
	{
		cmd_len = 0;
		while (argv[cmd_len]
		&& strcmp(argv[cmd_len], "|")
		&& strcmp(argv[cmd_len], ";"))
			cmd_len ++;

		if (cmd_len == 0)
			cmd_len = 1;
		else if (!strcmp(argv[0], "cd"))
		{
			if (cmd_len != 2)
				print_err ("error: cd: bad arguments\n", NULL);
			else if (chdir(argv[1]))
					print_err ("error: cd: cannot change directory to %\n", argv[1]);
		}
		else if (argv[cmd_len] && !strcmp(argv[cmd_len], "|"))
		{
			argv[cmd_len ++] = 0;

			pipe(pipes);
			if (fork() == 0)
			{
				dup2(pipes[1], STDOUT_FILENO);
				close(pipes[0]);
				close(pipes[1]);
				if (exec_cmd(in_fd, argv, envp))
					_exit(1);
			}
			else
			{
				close(pipes[1]);
				close(in_fd);
				in_fd = pipes[0];
			}
		}
		else
		{
			if (argv[cmd_len])
				argv[cmd_len++] = 0;

			if (fork() == 0)
			{
				if (exec_cmd(in_fd, argv, envp))
					_exit(1);
			}
			else
			{
				close(in_fd);
				while (waitpid(-1, NULL, WUNTRACED) != -1)
					in_fd = dup(STDIN_FILENO);
			}

		}



		while (argv[cmd_len] && !strcmp(argv[cmd_len], ";"))
			cmd_len++;

		argv += cmd_len;
	}


	if(close (in_fd) == -1)
		exit ((close(in_fd),
				print_err("error: fatal\n", NULL), errno));
	return (errno);
}