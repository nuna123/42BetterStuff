/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:05:25 by nroth             #+#    #+#             */
/*   Updated: 2023/04/02 15:05:27 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	main (int argc, char *argv[])
{
	char *str;
	char *str2;
	char *word;
	int maxlen = 0;
	int temp = 0;

	for (int i = 1; i < argc; i++)
	{
		str = argv[i];
		while (*str)
		{
			temp = 0;
			while (str[temp] && str[temp] != ' ')
				temp++;
			if (temp > maxlen)
				maxlen = temp;
			if (!str[temp])
				break;
			str += temp + 1;
		}
	}

	maxlen = (maxlen % 2 == 1 ? maxlen : maxlen + 1) + 4;
	for (int i = 0; i < maxlen + 2; i++)
		printf ("*");
	printf("\n");

	for (int i = 1; i < argc; i++)
	{
		str = argv[i];
		while (*str)
		{
			word = str;
			if (strchr(str, ' '))
			{
				str = strchr(str, ' ') + 1;
				*(strchr(word, ' ')) = 0;
			}
			else
				str = strchr(str, 0);

			printf ("*");
			if (strlen(word) % 2 == 0)
				printf (" ");
			for (int i = 0; i < ((maxlen - strlen(word)) / 2); i++)
				printf (" ");
			printf("%s", word);
			for (int i = 0; i < ((maxlen - strlen(word)) / 2); i++)
				printf (" ");
			printf ("*\n");
		}
	}
	for (int i = 0; i < maxlen + 2; i++)
		printf ("*");
	printf("\n");
}
