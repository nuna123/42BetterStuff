#include <stdio.h>
int	main (int argc, char *argv[])
{
	if (argc != 2)
		return (printf("what?\n"), 1);
	int sum = 0;
	int aces = 0;
	char *str = argv[1];
	for (;*str;str++)
	{
		if (*str <= '9' && *str >= '0')
			sum += *str - '0';
		else if (*str != 'A')
			sum += 10;
		else if (sum + 11 > 21)
			sum +=1;
		else if (sum + 11 <= 21)
			sum +=11;
	}

	if (sum == 21)
		printf("Blackjack!\n");
	else
		printf("%i\n", sum);
	return (0);
}