#include "philo.h"

void	*check_dead(void *p_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)p_data;
	while (1)
	{
		i = -1;
		while (++i < data->nbr_of_philos)
		{
			if (check_time(&data->philos[i]))
			{
				pthread_mutex_lock(&data->mutex_dead);
				data->is_dead = true;
				pthread_mutex_unlock(&data->mutex_dead);
				print_dead(&data->philos[i]);
				return (NULL);
			}
			if (data->five_args && everybody_ate(data))
			{
				print_all_eaten(data);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	while (!is_dead(philo) && !everybody_ate(philo->data))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*is_alone(void *alone)
{
	t_philo	*philo;

	philo = (t_philo *)alone;
	take_left_fork(philo);
	ft_usleep(philo->data->time_to_die);
	safe_print(philo, "is dead");
	pthread_mutex_unlock(&philo->left_fork);
	return (NULL);
}

int	case_one(t_data *data)
{
	if (pthread_create(&data->philos[0].thread, NULL, &is_alone,
			&data->philos[0]))
		return (0);
	if (pthread_join(data->philos[0].thread, NULL))
		return (0);
	return (1);
}

int	threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->nbr_of_philos == 1)
	{
		if (!case_one(data))
			return (0);
		return (1);
	}
	while (++i < data->nbr_of_philos)
	{
		data->philos[i].time_last_meal = get_time();
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]))
			return (0);
	}
	if (pthread_create(&data->monitor, NULL, &check_dead, data))
		return (0);
	i = -1;
	while (++i < data->nbr_of_philos)
		if (pthread_join(data->philos[i].thread, NULL))
			return (0);
	if (pthread_join(data->monitor, NULL))
		return (0);
	return (1);
}
