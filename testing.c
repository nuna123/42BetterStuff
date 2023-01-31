#include <stdio.h>
#include <unistd.h>

int main()
{
	//int i = 1;
	write(1, &("abc"[2]), 1);
	return 0;
}
