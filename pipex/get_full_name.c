
#include "pipex.h"

char *get_name(char *basename) 
{
	char	*fullname;
	int		pipees[2];

	fullname = NULL;
	pipe(pipees);
	pid_t child1 = fork();
	if(child1 == 0)
	{
		dup2(pipees[STDOUT_FILENO], STDOUT_FILENO);
		if (execve("/usr/bin/which", (char *[3]){"/usr/bin/which", basename, NULL}, NULL) == -1)
			exit(1);
	}
	dup2(pipees[STDIN_FILENO], STDIN_FILENO);
	fullname = get_next_line(STDIN_FILENO);
	close(pipees[0]);
	close(pipees[1]);
	return (fullname);
}

int main(int argc, char *argv[]) {
	printf("MAIN PROGRAM\n");
	char *fullname;

	if (argc > 1)
		fullname = get_name(argv[1]);
	else
		fullname = get_name("ls");

	printf("FULLNAME: {%s}\n", fullname);
	free(fullname);

	return 0;
}
