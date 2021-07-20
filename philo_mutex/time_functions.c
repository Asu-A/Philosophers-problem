#include "philo_one.h"

long	get_time(t_data *data)
{
	struct timeval	time;
	long			cur;

	pthread_mutex_lock(&data->time);
	gettimeofday(&time, NULL);
	pthread_mutex_unlock(&data->time);
	cur = time.tv_sec * 1000 + time.tv_usec * 0.001;
	return (cur);
}

int		my_sleep(long timer, t_data *data)
{
	long			start;
	long			offset;

	start = get_time(data);
	offset = get_time(data);
	while (offset < timer + start)
	{
		offset = get_time(data);
		usleep(50);
	}
	return (0);
}

int		ft_parser(char *argv[], t_data *data, int argc)
{
	if ((data->counter = ft_num(argv[1])) < 1)
		return (ft_error_msg("Wrong arguments\n", 16));
	if ((data->time_to_die = ft_num(argv[2])) < 1)
		return (ft_error_msg("Wrong arguments\n", 16));
	if ((data->time_to_eat = ft_num(argv[3])) < 1
		|| (data->time_to_sleep = ft_num(argv[4])) < 1)
		return (ft_error_msg("Wrong arguments\n", 16));
	if (argc == 6)
	{
		data->eat_counter = ft_num(argv[5]);
		if (data->eat_counter < 1)
			return (ft_error_msg("these philosophers are not hungry\n", 34));
	}
	else
		data->eat_counter = -1;
	return (0);
}

void	take_forks(t_philo *philo, int num)
{
	if (num == 1)
	{
		pthread_mutex_lock(&philo->forks[philo->left_fork]);
		ft_print(philo, " take left fork\n");
		pthread_mutex_lock(&philo->forks[philo->right_fork]);
		ft_print(philo, " take right fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->right_fork]);
		ft_print(philo, " take right fork\n");
		pthread_mutex_lock(&philo->forks[philo->left_fork]);
		ft_print(philo, " take left fork\n");
	}
}

void	drop_forks(t_philo *philo, int num)
{
	if (num == 1)
	{
		pthread_mutex_unlock(&philo->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	}
}
