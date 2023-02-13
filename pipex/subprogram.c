#include <stdio.h>
	
int main(int argc, char **argv) {
	printf("\tCHILD PROGRAM\n");
	for(int i = 0; i < argc; i++)
		printf("\targs [%i]: %s\n", i, argv[i]);
	return 1;
}