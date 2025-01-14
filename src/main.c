#include "philo.h"

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || c == '+' || c == '-')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long int	nb;
	int			sign;

	nb = 0;
	sign = 1;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (sign * nb);
}

bool	valid_input(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]) || ft_atol(argv[i]) < 1
				|| ft_atol(argv[i]) > INT_MAX)
				return (false);
		}
	}
	if (ft_atol(argv[1]) > 200 || ft_atol(argv[2]) <= 60
		|| ft_atol(argv[3]) <= 60 || ft_atol(argv[4]) <= 60)
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6 || !valid_input(argc, argv))
		return (write(2, "Error: Invalid arguments.\n", 26), 1);
	if (!init(&data, argc, argv))
		return (write(2, "Error: Initialization failed.\n", 30), 1);
	if (!threads(&data))
		return (write(2, "Error: Simulation failed.\n", 26), 1);
	free(data.philos);
	return (0);
}
