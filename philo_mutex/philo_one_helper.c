#include "philo_one.h"

void	change_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	philo->last_meal = get_time(philo->data) -
	philo->data->start_simulation;
	pthread_mutex_unlock(&philo->data->death);
	(philo->eat_counter > -1) ? philo->eat_counter-- : 0;
}

void	ft_init_philo(t_philo *philo, t_data *data, int i)
{
	philo->index = i + 1;
	if (i == data->counter - 1)
		philo->right_fork = 0;
	else
		philo->right_fork = i + 1;
	philo->left_fork = i;
	philo->last_meal = 0;
	philo->data = data;
	philo->eat_counter = data->eat_counter;
}

void	ft_join_treads(pthread_t *death, pthread_t *threads, int counter)
{
	int i;

	i = -1;
	while (++i < counter)
	{
		pthread_join(death[i], NULL);
		pthread_join(threads[i], NULL);
	}
}

void	ft_create_treds(t_data *data, pthread_t
	*threads, pthread_t *death, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data->counter)
	{
		pthread_create(&threads[i], NULL, ft_simulation, &philo[i]);
		pthread_create(&death[i], NULL, ft_death, &philo[i]);
		i += 2;
	}
	i = 1;
	while (i < data->counter)
	{
		pthread_create(&threads[i], NULL, ft_simulation, &philo[i]);
		pthread_create(&death[i], NULL, ft_death, &philo[i]);
		i += 2;
	}
}

void	ft_death_helper(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->output);
	pthread_mutex_lock(&philo->data->death);
	(philo->data->dead_flag2 != 1) ? write(1, str, ft_strlen(str)) : 0;
	drop_forks(philo, philo->index % 2);
	philo->data->dead_flag2 = 1;
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->data->output);
}
