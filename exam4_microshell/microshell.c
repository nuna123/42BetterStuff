#include "microshell.h"

void	print_err(char *s)
{
	while (s && *s)
	{
		write(STDERR_FILENO, s, 1);
		s++;
	}
}

int	exec_cmd(int in_fd, char *argv[], char *envp[])
{
		dup2(in_fd, STDIN_FILENO);

		close (in_fd);

		execve(argv[0], argv, envp);
		print_err("error: cannot execute ");
		print_err(argv[0]);
		print_err("\n");
		return (errno);
}

int main(int argc, char *argv[], char *env[])
{
	int	command_len;
	int	pipees[2];

	// int tmp_fd;
	int	in_fd;
	int	out_fd;


	if (argc <= 1)
		return (1);

	in_fd = dup(STDIN_FILENO);
	out_fd = dup(STDOUT_FILENO);

	argv++; //to skip argv[0] - program name
	while (argv[0])
	{
		command_len = 0;
		while (argv[command_len]
			&& strcmp("|", argv[command_len]) != 0
			&& strcmp(";", argv[command_len]) != 0)
			command_len++;

		if (command_len == 0)
			command_len = 1;
		else if (strcmp(argv[0], "cd") == 0)
		{
			if (command_len != 2)
				print_err("error: cd: bad arguments\n");
			else if (chdir(argv[1]) != 0)
			{
				print_err("error: cd: cannot change directory to ");
				print_err(argv[1]);
				print_err("\n");
			}
		}
		else
		{
			if (argv[command_len] && strcmp("|", argv[command_len]) == 0)// SHOULD BE REDIRECTED TO PIPE
			{
				pipe (pipees);
				argv[command_len ++] = 0;
				if (fork() == 0)
				{
					dup2(pipees[1], STDOUT_FILENO);
					close(pipees[0]);
					close(pipees[1]);
					if (exec_cmd(in_fd, argv, env))
						exit ((print_err("fatality!\n"), 1));
				}
				else
				{
					close (pipees[0]);
					close (in_fd);
					in_fd = pipees[0];
				}
			}
			else
			{
				if (argv[command_len])
					argv[command_len++] = 0;
				if (fork() == 0)
				{
					if (exec_cmd(in_fd, argv, env))
						exit ((print_err("fataliy!\n"), 1));
				}
				else
				{
					close(in_fd);
					while (waitpid(-1, NULL, WUNTRACED) != -1)
						in_fd = dup(STDIN_FILENO);
				}
			}
		}
		argv += command_len;
	}

	close(in_fd);
	close(out_fd);

	return (0);
}