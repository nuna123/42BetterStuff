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

t_philo *init_philo(int which, t_prog *prog)
{
	t_philo *philo;

	philo = &prog->philos[which - 1];

	philo->which = which;
	philo->prog = prog;
	philo->time_last_ate = prog->prog_init;
	philo->currently = THINKING;
	philo->eat_count = 0;

	return (philo);
}

void	announcment(int which, char *msg)
{
/* 	(void) which;
	(void) msg; */
	printf("%lu : PHILOSOPHER %i %s\n", get_timestamp_ms(NULL), which, msg);
	return ;
}

void	death(t_philo *philo)
{
	int i;

	i = -1;
	announcment(philo->which, IS_DEAD);
	while (++i < philo->prog->num_of_philos)
	{
		printf("detaching %lu\n",philo->prog->philo_threads[i] );
		pthread_detach((philo->prog->philo_threads[i]));
	}
		
	free_prog(philo->prog);
	exit(1);
}

void	*philosophize(void *philo_v)
{
	usleep(100);
	if (!philo_v)
		return (NULL);
	t_philo *philo = (t_philo *) philo_v;
	t_prog	*prog = philo->prog;

	int forks[2];
	//wait till forks unlocked, calc if dead yet
	//lock forks, wait eating time
	//unlock forks, wait sleeping time
	//loop

	//calc fork position, each philo uses WHICH and WHICH - 1
	// printf("which: %i; mum of forks: %i\n", philo->which , prog->num_of_philos);

	forks[0] = philo->which % prog->num_of_philos;
	forks[1] = philo->which - 1;

	// printf("philo %i: forks[%i, %i]\n", philo->which, forks[0], forks[1]);
	if (forks[0] == forks[1])
		exit((printf("SHIt %i", philo->which), free_prog(prog), 1));

	while (1)
	{
		pthread_mutex_lock(&prog->forks[forks[0]]);
		announcment(philo->which, TOOK_FORK);
		// printf("FORK: %i\n", forks[0]);

		pthread_mutex_lock(&prog->forks[forks[1]]);
		announcment(philo->which, TOOK_FORK);
// printf("FORK: %i\n", forks[1]);
		if (get_timestamp_ms(NULL) - philo->time_last_ate >= prog->time_to_die)
			death(philo);

		announcment(philo->which, IS_EATING);

		msleep(prog->time_to_eat);
		philo->time_last_ate = get_timestamp_ms(NULL);

		pthread_mutex_unlock(&prog->forks[forks[0]]);
		pthread_mutex_unlock(&prog->forks[forks[1]]);
		philo->eat_count ++;
		
		announcment(philo->which, IS_SLEEPING);
		msleep(prog->time_to_sleep);
		announcment(philo->which, IS_THINKING);
		msleep(10);
	}
	printf("THREAD RET\n");
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_prog *prog;
	t_philo *philo;

	if (argc == 5 || argc == 6)
		prog = init_prog(argc, argv);
	else
		prog = init_prog(5, (char *[]) {"philos", "2", "3000", "2000", "2000", NULL});

	int i= 0;
	int l = 0;

	while (i < prog->num_of_philos)
	{
		philo = init_philo(i + 1, prog);
		// l = pthread_create(&(prog->philo_threads[i]), NULL, philosophize, NULL);
		l = pthread_create(&(prog->philo_threads[i]), NULL, philosophize, (void *) philo);
		// usleep(100);
		i++;
	}
	
	i = -1;

	while (++i < prog->num_of_philos)
	{
		pthread_join(prog->philo_threads[i], NULL);
	}
	free_prog(prog);
	printf("MAIN RET\n");
	return (0);
}
