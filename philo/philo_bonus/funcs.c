/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:21:16 by nroth             #+#    #+#             */
/*   Updated: 2023/03/11 10:21:17 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

t_prog	*init_prog(int argc, char *argv[])
{
	t_prog	*prog;
	int		i;

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (NULL);
	prog->alive = TRUE;
	prog->num_of_philos = (int) ft_atoi(argv[1]);
	prog->prog_init = 0;
	prog->philos = malloc(sizeof(t_philo) * prog->num_of_philos);
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->num_of_philos);
	prog->philo_threads = malloc(sizeof(pthread_t) * prog->num_of_philos);
	if (!prog->philos || !prog->forks || !prog->philo_threads)
		return (free_prog(prog), NULL);
	i = -1;
	while (++i < prog->num_of_philos)
		pthread_mutex_init(&prog->forks[i], NULL);
	pthread_mutex_init(&prog->printing, NULL);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->num_to_eat = (unsigned int) -1;
	if (argc == 6)
		prog->num_to_eat = (unsigned int) ft_atoi(argv[5]);
	return (prog);
}

void	free_prog(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->num_of_philos)
	{
		printf("i: %i\n", i);
		if (prog->philo_threads)
			pthread_detach(prog->philo_threads[i]);
		if (prog->forks)
			pthread_mutex_destroy(&prog->forks[i]);
	}
	pthread_mutex_destroy(&prog->printing);
	free (prog->forks);
	free (prog->philo_threads);
	free (prog->philos);
	free (prog);
}

t_philo	*init_philo(int which, t_prog *prog)
{
	t_philo	*philo;

	philo = &prog->philos[which - 1];
	philo->which = which;
	philo->prog = prog;
	philo->time_last_ate = get_timestamp_ms(NULL);
	philo->currently = THINKING;
	philo->eat_count = 0;
	return (philo);
}

void	announcment(t_philo *philo, char *msg)
{
	if (philo->prog->alive == TRUE)
	{
		pthread_mutex_lock(&philo->prog->printing);
		if (philo->prog->alive == TRUE)
		{
			printf("%lu %i %s\n",
				get_timestamp_ms(NULL) - philo->prog->prog_init,
				philo->which, msg);
		}
		pthread_mutex_unlock(&philo->prog->printing);
	}
	return ;
}

int	check_pulse(t_philo *philo)
{
	if (philo->prog->alive == FALSE
		|| get_timestamp_ms(NULL) - philo->time_last_ate
		>= philo->prog->time_to_die)
	{
		announcment(philo, IS_DEAD);
		philo->prog->alive = FALSE;
		unlock_forks(philo);
		return (TRUE);
	}
	return (FALSE);
}
