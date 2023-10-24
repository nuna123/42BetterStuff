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
#include <errno.h>
t_prog	*init_prog(int argc, char *argv[])
{
	t_prog	*prog;

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (NULL);
	prog->alive = TRUE;
	prog->num_of_philos = (int) ft_atoi(argv[1]);
	prog->prog_init = 0;
	prog->forks_sema = malloc(sizeof(sem_t));
	prog->print_sema = malloc(sizeof(sem_t));

	prog->philos = malloc(sizeof(t_philo) * prog->num_of_philos);
	memset(prog->philos, 0, sizeof(t_philo) * prog->num_of_philos);
	
	prog->philo_pids = malloc(sizeof(pid_t) * prog->num_of_philos);
	if (!prog->philos || !prog->philo_pids)
		return (free_prog(prog), NULL);
	prog->time_to_die = ft_atoi(argv[2]);
	prog->time_to_eat = ft_atoi(argv[3]);
	prog->time_to_sleep = ft_atoi(argv[4]);
	prog->num_to_eat = (unsigned int) -1;
	if (argc == 6)
		prog->num_to_eat = (unsigned int) ft_atoi(argv[5]);
	return (prog);
}

void	open_semis(t_prog *prog)
{
	sem_t *sem = sem_open(FORK_NAME, O_CREAT, S_IRWXU, 1);
	printf("opening semis...fork val: %i\n", errno);

	// prog->forks_sema = sem_open(FORK_NAME, O_CREAT, 0666, 1);
	if (sem == SEM_FAILED)
	{
		printf("AAAAAAAAAAAAA\n");
		return ;
	}

printf("FORKS: waiting\n");
	sem_wait(sem);
	
	printf("FORKS: NICE!\n");
	printf("FORKS: posting sem\n");
	sem_post(sem);

	// prog->print_sema = sem_open(PRINT_NAME, O_CREAT, 0666, 1);
}


void	free_prog(t_prog *prog)
{
	free (prog->philos);

	sem_close(prog->print_sema);
	free(prog->print_sema);

	sem_close(prog->forks_sema);
	free(prog->forks_sema);

	free (prog->philo_pids);

	free (prog);
}


void	terminate_philos(t_prog *prog)
{
	int	i;

	i = -1;
	while (++i < prog->num_of_philos)
		kill(prog->philo_pids[i], SIGKILL);
}

t_philo	*init_philo(int which, t_prog *prog)
{
	t_philo	*philo;

	philo = &prog->philos[which - 1];
	philo->which = which;
	philo->prog = prog;
	philo->time_last_ate = get_timestamp_ms();
	philo->eat_count = 0;
	return (philo);
}

void	announcment(t_philo *philo, char *msg)
{
	if (philo->prog->alive == TRUE)
	{
		sem_wait(philo->prog->print_sema);
		if (philo->prog->alive == TRUE)
		{
			printf("%lu %i %s\n",
				get_timestamp_ms() - philo->prog->prog_init,
				philo->which, msg);
		}
		sem_post(philo->prog->print_sema);
	}
	return ;
}

int	check_pulse(t_philo *philo)
{
	if (philo->prog->alive == FALSE
		|| get_timestamp_ms() - philo->time_last_ate
		>= philo->prog->time_to_die)
	{
		announcment(philo, IS_DEAD);
		philo->prog->alive = FALSE;
		// unlock_forks(philo);
		free_prog(philo->prog);
		exit(0);
	}
	return (FALSE);
}
