/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:09:52 by nroth             #+#    #+#             */
/*   Updated: 2023/03/11 10:09:53 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"


void	*philosophize(void *vargp)
{
	int myid = *((int *) vargp);
	if (myid == 10)
		exit(0);

	printf("Thread I: %d \n", myid);
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_prog *prog;

	if (argc == 5 || argc == 6)
		prog = init_prog(argc, argv);
	else
		prog = init_prog(5, (char *[]) {"philos", "21", "10000", "1000", "1000", NULL});

	int i= 0;
	int l = 0;

	while (i < prog->num_of_philos)
	{
		l = pthread_create(&(prog->philo_threads[i]), NULL, philosophize, (void *) &i);
		// printf("%i - create ret val: %i\n",i, l);
		usleep(100);
		i++;
	}

	free_prog(prog);
	return (0);
}
