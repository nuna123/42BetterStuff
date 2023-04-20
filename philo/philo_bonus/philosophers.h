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

# include <stdio.h>
# include <stdlib.h>

#include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <signal.h>


# define OK				0
# define ERR			1

# define FALSE			0
# define TRUE			1

# define FORK_NAME		"/focks"
# define PRINT_NAME		"/printer"

# define TOOK_FORK		"has taken a fork"
# define IS_EATING		"is eating"
# define IS_SLEEPING	"is sleeping"
# define IS_THINKING	"is thinking"
# define IS_DEAD		"has very much died"

# define THINKING		'T'
# define EATING			'E'
# define SLEEPING		'S'

/* 
//SET BY TIME.H
struct timeval {
	time_t		tv_sec; // timeval_sec
	suseconds_t	tv_usec;// timeval micro sec
};
*/
typedef struct timeval	t_time;
struct					s_philo;

typedef struct s_prog
{
	int				num_of_philos;
	struct s_philo	*philos;

	sem_t			*forks_sema;
	sem_t			*print_sema;
	pid_t			*philo_pids;

	int				alive;
	unsigned long	prog_init;

	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;

	unsigned int	num_to_eat;
}	t_prog;

typedef struct s_philo
{
	int				which;
	unsigned long	time_last_ate;

	int				eat_count;

	t_prog			*prog;
}	t_philo;

//MAIN
void			unlock_forks(t_philo *philo);

// UTILS
int				ft_strlen(const char *s);
long			ft_atoi(const char *nptr);
unsigned long	get_timestamp_ms(void);
unsigned long	msleep(unsigned long ms);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

// FUNCS
t_prog			*init_prog(int argc, char *argv[]);
void			free_prog(t_prog *prog);
t_philo			*init_philo(int which, t_prog *prog);
void			announcment(t_philo *philo, char *msg);
int				check_pulse(t_philo *philo);
#endif