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


static void	philo_eat(t_philo *philo)
{
	if (check_pulse (philo) == TRUE
		|| (unsigned int) philo->eat_count >= philo->prog->num_to_eat)
	{
		/* philo->prog->alive = FALSE;
		unlock_forks(philo);
		return ; */
		free_prog(philo->prog);
		exit(0);
	}
	printf("waiting for fork...\n");
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
		exit((free_prog(philo->prog),1));
	prog = philo->prog;
	if (prog->num_of_philos == 1)
		exit((free_prog(philo->prog),1));
	if (prog->prog_init == 0)
		prog->prog_init = get_timestamp_ms();
	while (1 && prog->alive == TRUE)
	{
		if (philo->which % 2 == 1 && philo->eat_count == 0)
			msleep(prog->time_to_eat);
		philo_eat(philo);
		philo_do(philo, SLEEPING);
		philo_do(philo, THINKING);
	}
	printf ("HELLO FROM %i\n", philo->which);
	exit((printf("exiting...\n"), free_prog(prog), 0));
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

	// open_semis(prog);

	printf("fork name: {%s}\n", FORK_NAME);
	sem_t *sema = sem_open(FORK_NAME, O_CREAT, S_IRWXU, 1);

	printf("MAIN: waiting for semi...\n");
	sem_wait(sema);
	
	printf("MAIN: NICE!\n");
	printf("MAIN: posting sem\n");
	sem_post(sema);

	// i = 0;
/* 	printf("making philos...\n");+
	while (i < prog->num_of_philos)
	{
		philo = init_philo(i + 1, prog);
		printf("\nmaking philo %i...\n", i+ 1);

		prog->philo_pids[i] = fork();
		printf("PID %i...\n", prog->philo_pids[i]);

		if (prog->philo_pids[i] == 0)
		{
			open_semis(prog);
			philosophize(philo);
			exit (2);
		}
		msleep(1);
		i++;
	}

	int exit_stat;
	printf("%sPHILO PID: %i\nExit stat: %i%s\n",Purple , wait(&exit_stat), exit_stat, Black); //wait for any proc to exit

	terminate_philos(prog); //close all remaining processes */

	free_prog(prog); //free space

	return (0);
}
