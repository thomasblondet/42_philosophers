#include "philo.h"

void	actualize_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_time);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->mutex_time);
}

int	check_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_time);
	if (get_time() - philo->time_last_meal > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->mutex_time);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_time);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long time_in_ms)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_in_ms)
		usleep(100);
}
