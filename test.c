#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char *arr[] = {NULL};

	execve("scriklpt.sh", arr, arr);

	if (errno == 2)
		exit (127);
	else if (errno == 13)
		exit (126);
 
	printf("ERR: {%i: %s}\n",errno,  strerror(errno));



	return 0;
}
