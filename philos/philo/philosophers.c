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

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->forks[1]);
	pthread_mutex_unlock(philo->forks[0]);
}

static void	philo_eat(t_philo *philo)
{
	if (check_pulse (philo) == TRUE
		|| (unsigned int) philo->eat_count >= philo->prog->num_to_eat)
	{
		philo->prog->alive = FALSE;
		unlock_forks(philo);
		return ;
	}
	pthread_mutex_lock((philo->forks[0]));
	announcment(philo, TOOK_FORK);
	if (check_pulse (philo) == TRUE)
		return ;
	pthread_mutex_lock((philo->forks[1]));
	announcment(philo, TOOK_FORK);
	if (check_pulse (philo) == TRUE)
		return ;
	announcment(philo, IS_EATING);
	philo->time_last_ate = get_timestamp_ms(0);
	msleep(philo->prog->time_to_eat);
	unlock_forks(philo);
	philo->eat_count++;
}

static void	philo_do(t_philo *philo, char action)
{
	check_pulse (philo);
	if (philo->prog->alive == FALSE)
		return ;
	else if (action == THINKING)
		announcment(philo, IS_THINKING);
	else if (action == SLEEPING)
	{
		announcment(philo, IS_SLEEPING);
		msleep(philo->prog->time_to_sleep);
		check_pulse (philo);
	}
}

static void	*philosophize(void *philo_v)
{
	t_philo	*philo;
	t_prog	*prog;

	if (!philo_v)
		return (NULL);
	philo = (t_philo *) philo_v;
	prog = philo->prog;
	philo->forks[0] = &prog->forks[philo->which % prog->num_of_philos];
	philo->forks[1] = &prog->forks[philo->which - 1];
	if (prog->num_of_philos == 1)
		return (announcment(philo, TOOK_FORK_LEFT),
			msleep(prog->time_to_die), announcment(philo, IS_DEAD), NULL);
	while (1 && prog->alive == TRUE)
	{
		if (philo->which % 2 == 1 && philo->eat_count == 0)
			msleep(prog->time_to_eat / 2);
		philo_eat(philo);
		philo_do(philo, SLEEPING);
		philo_do(philo, THINKING);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_prog	*prog;
	t_philo	*philo;
	int		i;

	if (argc == 5 || argc == 6)
		prog = init_prog(argc, argv);
	else
		return (printf("Invalid number of args."), 1);
	i = 0;
	while (i < prog->num_of_philos)
	{
		philo = init_philo(i + 1, prog);
		pthread_create(&(prog->philo_threads[i]),
			NULL, philosophize, (void *) philo);
		i++;
	}
	i = -1;
	while (++i < prog->num_of_philos)
		pthread_join(prog->philo_threads[i], NULL);
	free_prog (prog);
	return (0);
}
