#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					nbr_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_nbr_of_meals;
	bool				five_args;
	bool				is_dead;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		mutex_full;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_time;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
	int					id;
}						t_philo;

int						init(t_data *data, int argc, char *argv[]);
int						ft_atoi(const char *str);

#endif