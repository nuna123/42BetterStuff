#include "./microshell.h"


void printerr(char *s)
{
	while (s && *s)
	{
		write(STDERR_FILENO, s, 1);
		s++;
	}
}

void	fatality (void)
{
	printerr("error: fatal\n");
	exit(1);
}

void	run_execve(int in_fd, int out_fd, char **command, char *envp[])
{
	pid_t	child;

	child = fork();
	if (child == -1)
		fatality();
	if (!child)
	{
		dup2(in_fd, STDIN_FILENO);
		dup2(out_fd, STDOUT_FILENO);

		close(in_fd);
		close(out_fd);

		execve(command[0], command, envp);
		printerr("error: cannot execute ");
		printerr(command[0]);
		printerr("\n");
		exit (errno);
	}
	waitpid(child, NULL, 0);
}


int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	int		argv_end;
	int		in_fd;
	int		out_fd;
	int		pipees[2];

	if(argc < 2)
		return (1);

	in_fd = dup(STDIN_FILENO);
	out_fd = dup(STDOUT_FILENO);

	argv++;
	while (argv[0])
	{
		// A command is not one arg long, get to the end of command
		argv_end = 0;
		while (argv[argv_end]
			&& strcmp(argv[argv_end], "|") != 0
			&& strcmp(argv[argv_end], ";") != 0)
				argv_end++;
		if (argv_end == 0)
			argv_end = 1;
		else if (!strcmp(argv[0], "cd"))
		{
			if (argv_end != 2)
				printerr("error: cd: bad arguments\n");
			else
			{
				if(chdir(argv[1]))
				{
					printerr("error: cd: cannot change directory to ");
					printerr(argv[1]);
					printerr("\n");
				}
			}
		}
		else
		{
				//Run command with execve
			//check if needs to update in_fd
			if (argv[argv_end] && !strcmp(argv[argv_end], "|"))
			{
				argv[argv_end++] = 0;
				pipe(pipees);
				close(out_fd);
				out_fd = pipees[1];
				run_execve(in_fd, out_fd, argv, envp);
				close (in_fd);
				close (out_fd);

				in_fd = pipees[0];
				out_fd = dup(STDOUT_FILENO);
			}
			else
			{
				if (argv[argv_end])
					argv[argv_end++] = 0;
				run_execve(in_fd, out_fd, argv, envp);

				dup2(STDIN_FILENO, in_fd);
				dup2(STDOUT_FILENO, out_fd);
			}
			if (!argv[argv_end])
			{
				close (in_fd);
				close (out_fd);
			}
		}

		while (argv[argv_end] && strcmp(argv[argv_end], ";") == 0)
			{argv_end++;}
		argv += argv_end;
		}

	close(in_fd);
	return (0);
}