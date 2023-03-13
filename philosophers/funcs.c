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
	prog->prog_init = get_timestamp_ms(NULL);
	prog->philos = malloc(sizeof(t_philo) * prog->num_of_philos);
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->num_of_philos);
	prog->philo_threads = malloc(sizeof(pthread_t) * prog->num_of_philos);
	if (!prog->philos || !prog->forks || !prog->philo_threads)
		return (free(prog->philos), free(prog->forks),free (prog->philo_threads), NULL);
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

/*  	i = -1;
	while (++i < prog->num_of_philos)
		pthread_detach((prog->philo_threads[i])); */
	i = -1;
	while (++i < prog->num_of_philos)
		pthread_mutex_destroy(&prog->forks[i]);
	pthread_mutex_destroy(&prog->printing);
	free (prog->forks);
	free (prog->philo_threads);
	free (prog->philos);
	free (prog);
}
