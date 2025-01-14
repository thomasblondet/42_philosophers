#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_mutex_init(&data->philos[i].left_fork, NULL))
		{
			write(2, "Error: mutex initialization failed.\n", 36);
			while (i >= 0)
				pthread_mutex_destroy(&data->philos[i--].left_fork);
			return (0);
		}
		data->philos[i].id = i + 1;
		i++;
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_full, NULL))
		return (pthread_mutex_destroy(&data->mutex_dead), 0);
	if (pthread_mutex_init(&data->mutex_print, NULL))
		return (pthread_mutex_destroy(&data->mutex_dead),
			pthread_mutex_destroy(&data->mutex_full), 0);
	if (pthread_mutex_init(&data->mutex_time, NULL))
		return (pthread_mutex_destroy(&data->mutex_dead),
			pthread_mutex_destroy(&data->mutex_full),
			pthread_mutex_destroy(&data->mutex_print), 0);
	return (1);
}

void	link_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philos - 1)
	{
		data->philos[i].right_fork = &data->philos[i + 1].left_fork;
		i++;
	}
	data->philos[i].right_fork = &data->philos[0].left_fork;
	i = 0;
	while (i < data->nbr_of_philos)
	{
		data->philos[i].data = data;
		i++;
	}
}

void	input_init(t_data *data, int argc, char *argv[])
{
	data->nbr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->max_nbr_of_meals = ft_atoi(argv[5]);
		data->five_args = true;
	}
}

int	init(t_data *data, int argc, char *argv[])
{
	input_init(data, argc, argv);
	data->philos = malloc(data->nbr_of_philos * sizeof(t_philo));
	if (!data->philos)
		return (0);
	link_forks(data);
	if (!init_forks(data) || !init_mutexes(data))
		return (free(data->philos), 0);
	return (1);
}
