#include "philo_two.h"

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
		sem_wait(philo->data->output);
		write(1, res, ft_strlen(res));
		sem_post(philo->data->output);
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
			take_forks(philo);
		if (ft_print(philo, " eating\n") == 1)
		{
			drop_forks(philo);
			break ;
		}
		my_sleep(philo->data->time_to_eat, philo->data);
		drop_forks(philo);
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
	while (get_time(philo->data) - philo->data->start_simulation
		< philo->data->time_to_die + philo->last_meal + 1)
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
	sem_t		*forks;
	pthread_t	threads[data->counter];
	pthread_t	death[data->counter];
	t_philo		philo[data->counter];
	int			i;

	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, S_IRWXU, data->counter);
	fill_data(data);
	i = -1;
	while (++i < data->counter)
	{
		ft_init_philo(&philo[i], data, i);
		philo[i].forks = forks;
		philo[i].death = &death[i];
	}
	data->start_simulation = get_time(philo->data);
	i = -1;
	while (++i < data->counter)
	{
		pthread_create(&threads[i], NULL, ft_simulation, &philo[i]);
		pthread_create(&death[i], NULL, ft_death, &philo[i]);
	}
	ft_join_treads(death, threads, data->counter, data);
	sem_close(forks);
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
