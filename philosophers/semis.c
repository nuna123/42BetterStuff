#include <fcntl.h>			/* For O_* constants */
#include <sys/stat.h>		/* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char * argv[])
{
	char * name = "/forks";
	sem_t * semaphore;

	//If semaphore with name does not exist, then create it with VALUE
	printf("Open or Create a named semaphore, %s, its value is %d\n", name, 1);
	semaphore = sem_open(name, O_CREAT, 0666, 0);

	pid_t child = fork();
	if (child == 0)
	{
		printf("CHILD: 1\n");
		sem_post(semaphore);

		usleep(100);

		sem_wait(semaphore);
		
		printf("CHILD: 3\n");
		sem_post(semaphore);

		sem_close(semaphore);
		exit (0);
	}

	sem_wait(semaphore);
	printf("PARENT: 2\n");
	sem_post(semaphore);


	wait(NULL);
	sem_wait(semaphore);
	printf("PARENT: 4\n");

	sem_close(semaphore);
	sem_unlink(name);
	return 0;
}
