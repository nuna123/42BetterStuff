
#include <sys/time.h>
/* 
//set by time.h
struct timeval {
	time_t      tv_sec;
	suseconds_t tv_usec;
};

typedef struct timeval t_time;

philosopher struct
typedef struct s_philo
{
	int which; // from 1 to PHILOSOPHERS NUM
	t_time	time_last_ate; //start time last ate, initialte to program start
	
	t_time	time_sleeping; //will be set every time philosopher starts sleeping, to wake up once done

	int eat_count; //init to 0, should increment each time 

	char currently; // S = sleeping, E = eating, T = thinking

	struct s_philo *prev;
	struct s_philo *next;

} t_philo;

typedef struct s_prog
{
	t_philo *philosophers; // linked list of filos
	int num_of_philos; //also num of forks

	int *forks; // an array, index tied to position on table, will be set to 0 if available, 1 if taken;

	t_time time_to_die;
	t_time time_to_eat;
	t_time time_to_sleep;

	int num_to_eat; //number_of_times_each_philosopher_must_eat, optional value, if not set will be -1


} t_prog;

 */