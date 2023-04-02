#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


int ranks;
int max_width;

void write_line(int width)
{
	if (width < 1)
		return ;
	for (int i = 0; i < (max_width - (width + 2)) / 2; i++)
		printf(" ");
	printf("/");
	for (int i = 0; i < width; i++)
		printf("*");
	printf("\\");
	for (int i = 0; i < (max_width - (width + 2)) / 2; i++)
		printf(" ");
	printf("\n");
}

void get_max_width ()
{
	int width = -3;
	for (int rank = 1; rank <= ranks; rank++)
	{
		if (rank == 0)
			width = 3;
		else
			width += 2 * (3 + ((rank-1) / 3));
		for (int i = 1; i < (3 + (rank - 1)); i++)
			width += 2;
	}
	max_width = width;
}

void make_door(int width)
{
	int door_size = (ranks % 2 == 1 ? ranks : ranks - 1);
	if (width < 1)
		return ;
	for (int i = 0; i < (max_width - ((width - door_size) + 2)) / 2; i++)
		printf(" ");
	printf("/");
	for (int i = 0; i < (width- door_size) / 2 - 2; i++)
		printf("*");
	for (int i = 0; i < door_size; i++)
		printf("|");
	for (int i = 0; i < (width- door_size) / 2; i++)
		printf("*");

	printf("\\");
	for (int i = 0; i < (max_width - ((width - door_size) + 2)) / 2; i++)
		printf(" ");
	printf("%i\n", width);
}

int main(int argc, char **argv)
{
	if (argc != 2 || !(ranks = atoi(argv[1])))
		exit (0);
	
	get_max_width();

	printf("RANKS: %i\n", ranks);
	printf("MAX_WDTH: %i\n", max_width);


	int width = -3;
	for (int rank = 1; rank < ranks; rank++)
	{
		if (rank == 0)
			width = 3;
		else
			width += 2 * (3 + ((rank-1) / 3));
		write_line(width - 2);
		for (int i = 1; i < (3 + (rank - 1)); i++)
		{
			write_line(width);
			width += 2;
		}
	}
	width += 2 * (3 + ((ranks-1) / 3));
	for (int i = 1; i < (3 + (ranks)); i++)
	{
		if (i <= (ranks % 2 == 1 ? ranks : ranks - 1))
			write_line(width - 2);
		else
		{
			make_door(width);
		}
			
		width += 2;
	}

	return (0);
}