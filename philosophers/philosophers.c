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

void	announcment(t_philo *philo, char *msg)
{
	if (philo->prog->alive == TRUE)
	{
		pthread_mutex_lock(&philo->prog->printing);
		printf("%lu : PHILOSOPHER %i %s\n", get_timestamp_ms(NULL), philo->which, msg);
		pthread_mutex_unlock(&philo->prog->printing);
	}

	return ;
}

void	death(t_philo *philo)
{
	int i;

	i = -1;
	announcment(philo, IS_DEAD);
	while (++i < philo->prog->num_of_philos)
	{
		printf("%i: detaching %lu\n",i, philo->prog->philo_threads[i] );
		pthread_detach((philo->prog->philo_threads[i]));
	}
	printf("done detaching\n");
	// free_prog(philo->prog);
	//exit(1);
}
	//wait till forks unlocked, calc if dead yet
	//lock forks, wait eating time
	//unlock forks, wait sleeping time
	//loop

	//calc fork position, each philo uses WHICH and WHICH - 1
	// printf("which: %i; mum of forks: %i\n", philo->which , prog->num_of_philos);


void	philo_eat_odd(t_philo *philo)
{
	if (philo->prog->alive == FALSE)
		return ;
	pthread_mutex_lock((philo->forks[1]));
	announcment(philo, TOOK_FORK);
	if (get_timestamp_ms(NULL) - philo->time_last_ate >= philo->prog->time_to_die)
	{
		announcment(philo, IS_DEAD);
		philo->prog->alive = FALSE;
		return ;
	}
	pthread_mutex_lock((philo->forks[0]));
	announcment(philo, TOOK_FORK);
	if (get_timestamp_ms(NULL) - philo->time_last_ate >= philo->prog->time_to_die)
	{
		printf("philo %i UNALIVE!\n", philo->which);
		philo->prog->alive = FALSE;
		return ;
	}
	if (philo->prog->alive == FALSE)
		return ;
	announcment(philo, IS_EATING);
	msleep(philo->prog->time_to_eat);
	if (philo->prog->alive == FALSE)
		return ;
	philo->time_last_ate = get_timestamp_ms(NULL);
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
	philo->eat_count++;
}

void	philo_eat_even(t_philo *philo)
{
	if (philo->prog->alive == FALSE)
		return ;
	pthread_mutex_lock((philo->forks[0]));
	announcment(philo, TOOK_FORK);
	if (get_timestamp_ms(NULL) - philo->time_last_ate >= philo->prog->time_to_die)
	{
		printf("philo %i UNALIVE!\n", philo->which);
		philo->prog->alive = FALSE;
		return ;
	}
	pthread_mutex_lock((philo->forks[1]));
	announcment(philo, TOOK_FORK);
	if (get_timestamp_ms(NULL) - philo->time_last_ate >= philo->prog->time_to_die)
	{
		printf("philo %i UNALIVE!\n", philo->which);
		philo->prog->alive = FALSE;
		return ;
	}
	if (philo->prog->alive == FALSE)
		return ;
	announcment(philo, IS_EATING);
	msleep(philo->prog->time_to_eat);
	if (philo->prog->alive == FALSE)
		return ;
	philo->time_last_ate = get_timestamp_ms(NULL);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
	philo->eat_count++;
}


void	*philosophize(void *philo_v)
{
	if (!philo_v)
		return (NULL);
	t_philo *philo = (t_philo *) philo_v;
	t_prog	*prog = philo->prog;

	int forks[2];

	forks[0] = philo->which % prog->num_of_philos;
	forks[1] = philo->which - 1;
	if (forks[0] == forks[1])
		exit((printf("SHIt %i", philo->which), free_prog(prog), 1));
	philo->forks[0] = &prog->forks[forks[0]];
	philo->forks[1] = &prog->forks[forks[1]];

	while (1 && prog->alive == TRUE)
	{
		if (philo->which % 2 == 0)
			philo_eat_odd(philo);
		else
			philo_eat_even(philo);

		if (philo->prog->alive == TRUE)
		{
			printf("PHILO %i eat count: %i\n", philo->which, philo->eat_count);

			announcment(philo, IS_SLEEPING);
			msleep(prog->time_to_sleep);
		}
		if (philo->prog->alive == TRUE)
		{
			announcment(philo, IS_THINKING);
		}
	}
	return (NULL);
}

int main(int argc, char *argv[])
{
	t_prog *prog;
	t_philo *philo;

	if (argc == 5 || argc == 6)
		prog = init_prog(argc, argv);
	else
		prog = init_prog(5, (char *[]) {"./philo", "4", "310", "200", "100", NULL});

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
