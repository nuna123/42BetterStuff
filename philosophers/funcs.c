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

t_prog *init_prog(int argc, char *argv[])
{
	t_prog	*prog;
	int		i;

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (NULL);
	
	prog->num_of_philos = (int) ft_atoi(argv[1]);
	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->num_of_philos);

	i = -1;
	while (++i < prog->num_of_philos)
		pthread_mutex_init(&prog->forks[i], NULL);

	prog->philo_threads = malloc(sizeof(pthread_t) * prog->num_of_philos);
	if (!prog->philo_threads)
		return (free(prog->forks), NULL);

	prog->time_to_die = ft_atoi(argv[2]) * 1000;
	prog->time_to_eat = ft_atoi(argv[3]) * 1000;
	prog->time_to_sleep = ft_atoi(argv[4]) * 1000;
	prog->num_to_eat = -1;
	if (argc == 6)
		prog->num_to_eat = (int) ft_atoi(argv[5]);

	return (prog);
}

void	free_prog(t_prog *prog)
{
	int i;

	i = -1;
	while (++i < prog->num_of_philos)
		pthread_join((prog->philo_threads[i]), NULL);
	i = -1;
	while (++i < prog->num_of_philos)
		pthread_mutex_destroy(&prog->forks[i]);
	free (prog->forks);
	free (prog->philo_threads);
	free(prog);
}
