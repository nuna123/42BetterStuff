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

int	check_pulse(t_philo *philo)
{
	if (philo->prog->alive == FALSE
		|| get_timestamp_ms() - philo->time_last_ate
		>= philo->prog->time_to_die)
	{
		announcment(philo, IS_DEAD);
		philo->prog->alive = FALSE;
		free_prog(philo->prog);
		exit(0);
	}
	return (FALSE);
}

static void	philo_eat(t_philo *philo)
{
	if (check_pulse (philo) == TRUE
		|| (unsigned int) philo->eat_count >= philo->prog->num_to_eat)
	{
		free_prog(philo->prog);
		exit(0);
	}
	sem_wait(philo->prog->forks_sema);
	announcment(philo, TOOK_FORK);
	if (check_pulse (philo) == TRUE)
		return ;
	sem_wait(philo->prog->forks_sema);
	announcment(philo, TOOK_FORK);
	if (check_pulse (philo) == TRUE)
		return ;
	announcment(philo, IS_EATING);
	philo->time_last_ate = get_timestamp_ms();
	msleep(philo->prog->time_to_eat);
	sem_post(philo->prog->forks_sema);
	sem_post(philo->prog->forks_sema);
	philo->eat_count++;
}

static void	philo_do(t_philo *philo, char action)
{
	check_pulse (philo);
	if (philo->prog->alive == FALSE)
		return ;
	else if (action == THINKING)
	{
		announcment(philo, IS_THINKING);
		if (philo->prog->num_of_philos % 2 == 1)
			msleep(philo->prog->time_to_eat / 2);
	}
	else if (action == SLEEPING)
	{
		announcment(philo, IS_SLEEPING);
		msleep(philo->prog->time_to_sleep);
		check_pulse (philo);
	}
}

static void	philosophize(t_philo *philo)
{
	t_prog	*prog;

	if (!philo)
		exit((free_prog(philo->prog), 1));
	prog = philo->prog;
	if (prog->prog_init == 0)
		prog->prog_init = get_timestamp_ms();
	if (prog->num_of_philos == 1)
		exit ((announcment(philo, TOOK_FORK),
				msleep(prog->time_to_die), announcment(philo, IS_DEAD), 0));
	while (1 && prog->alive == TRUE)
	{
		if (philo->which % 2 == 0 && philo->eat_count == 0)
			msleep(prog->time_to_sleep);
		philo_eat(philo);
		philo_do(philo, SLEEPING);
		philo_do(philo, THINKING);
	}
	exit((printf("Wtf happened? exiting...\n"), free_prog(prog), 0));
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
	open_semis(prog);
	i = -1;
	prog->prog_init = get_timestamp_ms();
	while (++i < prog->num_of_philos)
	{
		philo = init_philo(i + 1, prog);
		prog->philo_pids[i] = fork();
		if (prog->philo_pids[i] == 0)
		{
			philosophize(philo);
			exit (2);
		}
	}
	wait(NULL);
	terminate_philos(prog);
	free_prog(prog);
	return (0);
}
