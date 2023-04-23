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

	prog = malloc(sizeof(t_prog));
	if (!prog)
		return (NULL);
	prog->alive = TRUE;
	prog->num_of_philos = (int) ft_atoi(argv[1]);
	prog->prog_init = 0;
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
	sem_unlink(PRINT_NAME);
	sem_unlink(FORK_NAME);
	prog->forks_sema = sem_open(FORK_NAME, O_CREAT, 0666, prog->num_of_philos);
	prog->print_sema = sem_open(PRINT_NAME, O_CREAT, 0666, 1);
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
	int		msg_len;
	long	ts;

	if (philo->prog->alive == TRUE)
	{
		sem_wait(philo->prog->print_sema);
		if (philo->prog->alive == TRUE)
		{
			ts = get_timestamp_ms() - philo->prog->prog_init;
			printf("%lu %i %s\n",
				ts - (ts % 10),
				philo->which, msg);
		}
		msg_len = 0;
		while (msg[msg_len])
			msg_len++;
		msg_len++;
		if (ft_strncmp(IS_DEAD, msg, msg_len))
			sem_post(philo->prog->print_sema);
	}
	return ;
}

/* 			sem_getvalue(philo->prog->forks_sema, &msg_len);
			printf ("\t\tforks: %i\n", msg_len); */
