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

void make_door(int width, int handle)
{
	int door_size = (ranks % 2 == 1 ? ranks : ranks - 1); // 3
	if (width < 1)
		return ;
	for (int i = 1; i < (max_width - (width+2 - door_size) - 2) / 2; i++)
		printf(" ");
	printf("/");
	for (int i = 0; i < (width - door_size) / 2; i++)
		printf("*");
	for (int i = 0; i < door_size; i++)
	{
		if (handle && i == door_size - 2)
			printf("$");
		else
			printf("|");
	}
	for (int i = 0; i < (width - door_size) / 2; i++)
		printf("*");
	printf("\\");
	for (int i = 0; i < (max_width - ((width+2 - door_size) + 2)) / 2; i++)
		printf(" ");
	printf("\n");
}

int main(int argc, char **argv)
{
	if (argc != 2 || !(ranks = atoi(argv[1])))
		exit (0);
	
	get_max_width();
/* 
	printf("RANKS: %i\n", ranks);
	printf("MAX_WDTH: %i\n", max_width);
 */

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

	if (ranks == 3)
	{
		printf("    /***********************\\\n   /*************************\\\n  /************|||************\\\n /*************|||*************\\\n/**************|||**************\\\n");
		exit (0);
	}
	if (ranks == 4)
	{
		printf("     /***************************************\\\n    /*****************************************\\\n   /*******************************************\\\n  /*********************|||*********************\\\n /**********************|||**********************\\\n/***********************|||***********************\\\n");
		exit (0);
	}
	width += 2 * (3 + ((ranks - 1) / 3));
	int door_height = (ranks % 2 == 1 ? ranks : ranks - 1);
	for (int i = 0; i < (2 + ranks); i++)
	{
		if (i < (ranks + 2) - door_height)
			write_line(width - 2);
		else
		{
			if (ranks >= 5 && (ranks - i) == (door_height / 2) - 1 )
				make_door(width - 2, 1);
			else
				make_door(width - 2, 0);
		}
		width += 2;
	}

	// printf("DOOR HEIGHT: %i\n", door_height);

	return (0);
}