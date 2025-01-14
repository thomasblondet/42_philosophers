#include "philo.h"

void	increment_full(t_data *data)
{
	pthread_mutex_lock(&data->mutex_full);
	data->full_philo_count++;
	pthread_mutex_unlock(&data->mutex_full);
}

int	is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_full);
	if (philo->meal_count == philo->data->max_nbr_of_meals)
	{
		pthread_mutex_unlock(&philo->data->mutex_full);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_full);
	return (0);
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	return (0);
}

int	everybody_ate(t_data *data)
{
	pthread_mutex_lock(&data->mutex_full);
	if (data->full_philo_count == data->nbr_of_philos)
	{
		pthread_mutex_unlock(&data->mutex_full);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_full);
	return (0);
}
