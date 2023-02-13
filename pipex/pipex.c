
/* char* argv[] = { "/usr/bin/ls", NULL };
	char buffer[100];
	int pid;
	int pipees[2];
	
	pipe(pipees);
	printf("STDIN: {%i}; STDOUT: {%i}\n", STDIN_FILENO, STDOUT_FILENO);

	int child1 = fork();
	if(child1 == 0)
	{
		close(pipees[0]);
		dup2(pipees[1], STDOUT_FILENO);
		
		if (execve("/usr/bin/ls", argv, NULL) == -1)
			exit(1);
		exit(0);
	}

	pid_t child2 = fork();
	if(child2 == 0)
	{
		dup2(pipees[0], STDIN_FILENO);
		
		read(STDIN_FILENO,&buffer, 100);
		printf("BUFFER: {%s}}\n", buffer);
		exit(0);
	}
	printf("STDIN: {%i}; STDOUT: {%i}\n", STDIN_FILENO, STDOUT_FILENO);
	printf("BUFFER: {%s}}\n", buffer);

	close(pipees[0]);
	close(pipees[1]);

	int status;
	waitpid(child2, &status, 0); */