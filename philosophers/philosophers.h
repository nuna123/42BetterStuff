/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 10:02:00 by nroth             #+#    #+#             */
/*   Updated: 2023/03/11 10:02:01 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

#define OK	0
#define ERR	1

#define FORK_TAKEN	1
#define FORK_FREE	0

/* 
//SET BY TIME.H
struct timeval {
	time_t		tv_sec; // timeval_sec
	suseconds_t	tv_usec;// timeval micro sec
};
*/
typedef struct timeval t_time;

typedef struct s_philo
{
	int which;				// from 1 to PHILOSOPHERS NUM
	t_time	time_last_ate;	//start time last ate, initialte to program start
	
	t_time	time_sleeping;	//will be set every time philosopher starts sleeping, to wake up once done

	int eat_count;			//init to 0, should increment each time 

	char currently;			// S = sleeping, E = eating, T = thinking

	struct s_philo *prev;
	struct s_philo *next;

} t_philo;


typedef struct s_prog
{
	t_philo *philosophers;		// linked list of filos ??
	int num_of_philos;			//also num of forks

//NO	int *forks;					// an array, index tied to position on table, will be set to 0 if available, 1 if taken;
	pthread_mutex_t *forks;			//each philo will lock the forks they use while eating, release when finished

	pthread_t	*philo_threads;

	suseconds_t time_to_die;
	suseconds_t time_to_eat;
	suseconds_t time_to_sleep;

	int num_to_eat;			//number_of_times_each_philosopher_must_eat, optional value, if not set will be -1
} t_prog;


// UTILS
int		ft_strlen(const char *s);
long	ft_atoi(const char *nptr);

// FUNCS
t_prog	*init_prog(int argc, char *argv[]);
void	free_prog(t_prog *prog);

#endif