#include "philo_one.h"

int		ft_print(t_philo *philo, char *str)
{
	char	*res;
	long	moment;
	char	*tmp;

	if (philo->data->dead_flag != 0 || philo->eat_counter == 0)
		return (1);
	res = ft_create_str(philo->index, str);
	moment = get_time(philo->data) - philo->data->start_simulation;
	tmp = res;
	res = ft_strjoin(ft_itoa((int)moment), res);
	free(tmp);
	if (philo->data->dead_flag == 0)
	{
		pthread_mutex_lock(&philo->data->output);
		write(1, res, ft_strlen(res));
		pthread_mutex_unlock(&philo->data->output);
	}
	if (philo->data->dead_flag != 0)
		return (1);
	if (ft_strncmp(str, " eating", 7) == 0)
		change_last_meal(philo);
	free(res);
	return (0);
}

void	*ft_simulation(void *args)
{
	t_philo			*philo;

	philo = (t_philo*)args;
	while (1)
	{
		if (philo->data->dead_flag != 1)
			take_forks(philo, philo->index % 2);
		if (ft_print(philo, " eating\n") == 1)
		{
			drop_forks(philo, philo->index % 2);
			break ;
		}
		my_sleep(philo->data->time_to_eat, philo->data);
		drop_forks(philo, philo->index % 2);
		if (ft_print(philo, " sleeping\n") == 1)
			break ;
		my_sleep(philo->data->time_to_sleep, philo->data);
		if (ft_print(philo, " thinking\n") == 1)
			break ;
	}
	return (args);
}

void	*ft_death(void *args)
{
	t_philo	*philo;
	char	*str;
	char	*num_str;
	long	moment;
	char	*tmp;

	philo = (t_philo*)args;
	while (get_time(philo->data) - philo->data->start_simulation <
		philo->last_meal + philo->data->time_to_die + 1)
		if (philo->data->dead_flag != 0 || philo->eat_counter == 0)
			return (args);
	philo->data->dead_flag = 1;
	str = ft_itoa(philo->index);
	str = ft_strjoin(str, " dead\n");
	moment = get_time(philo->data) - philo->data->start_simulation;
	num_str = ft_strjoin(ft_itoa((int)moment), " ");
	tmp = str;
	str = ft_strjoin(num_str, str);
	free(tmp);
	ft_death_helper(philo, str);
	free(str);
	return (args);
}

void	ft_get_data(t_data *data)
{
	pthread_mutex_t	forks[data->counter];
	pthread_t		threads[data->counter];
	pthread_t		death[data->counter];
	t_philo			philo[data->counter];
	int				i;

	pthread_mutex_init(&data->output, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->time, NULL);
	i = -1;
	while (++i < data->counter)
	{
		pthread_mutex_init(&forks[i], NULL);
		ft_init_philo(&philo[i], data, i);
		philo[i].forks = forks;
		philo[i].death = &death[i];
	}
	data->start_simulation = get_time(data);
	ft_create_treds(data, threads, death, philo);
	ft_join_treads(death, threads, data->counter);
	pthread_mutex_destroy(&data->output);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->time);
	while (i-- > 0)
		pthread_mutex_destroy(&forks[i]);
}

int		main(int argc, char *argv[])
{
	t_data	data;

	data.dead_flag = 0;
	data.dead_flag2 = 0;
	if (argc != 5 && argc != 6)
		return (ft_error_msg("wrong arguments\n", 16));
	if (ft_parser(argv, &data, argc) < 0)
		return (1);
	ft_get_data(&data);
	return (0);
}
