// C program for the above approach

#include <stdarg.h>
#include <stdio.h>

// Variadic function to add numbers
int AddNumbers(char *n, ...)
{
	int Sum = 0;

	// Declaring pointer to the
	// argument list
	va_list ptr;

	// Initializing argument to the
	// list pointer
	va_start(ptr, n);
	printf("\nstr n: %s\n", n);

	for (int i = 0; i < 45; i++)
	{
		Sum = va_arg(ptr, int);
	}


	// Ending argument list traversal
	va_end(ptr);

	return Sum;
}

// Driver Code
int main()
{
	printf("\n{%x} \n", 2);

	printf("\n");

	return 0;
}
