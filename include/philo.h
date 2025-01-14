#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					nbr_of_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					max_nbr_of_meals;
	int					full_philo_count;
	long				start_time;
	bool				five_args;
	bool				is_dead;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		mutex_full;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_time;
	pthread_t			monitor;
	t_philo				*philos;
}						t_data;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
	long				time_last_meal;
	int					meal_count;
	int					id;
}						t_philo;

/* init */
int						init(t_data *data, int argc, char *argv[]);
/* threads */
int						threads(t_data *data);
/* actions */
void					eating(t_philo *philo);
void					take_left_fork(t_philo *philo);
void					take_right_fork(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);
/* safe checks */
int						is_dead(t_philo *philo);
int						is_full(t_philo *philo);
void					increment_full(t_data *data);
int						everybody_ate(t_data *data);
/* print */
void					safe_print(t_philo *philo, const char *message);
void					print_dead(t_philo *philo);
void					print_all_eaten(t_data *data);
/* time */
int						check_time(t_philo *philo);
void					actualize_meal_time(t_philo *philo);
long					get_time(void);
void					ft_usleep(long time_in_ms);
/* utils */
long					ft_atol(const char *str);

#endif