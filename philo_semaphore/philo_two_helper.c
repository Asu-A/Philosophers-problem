#include "philo_two.h"

void	ft_init_philo(t_philo *philo, t_data *data, int i)
{
	philo->index = i + 1;
	philo->data = data;
	philo->eat_counter = data->eat_counter;
	philo->last_meal = 0;
}

void	ft_join_treads(pthread_t *death,
		pthread_t *threads, int counter, t_data *data)
{
	int i;

	i = -1;
	while (++i < counter)
	{
		pthread_join(death[i], NULL);
		pthread_join(threads[i], NULL);
	}
	sem_close(data->output);
	sem_close(data->death);
	sem_close(data->wait);
	sem_close(data->time);
}

void	change_last_meal(t_philo *philo)
{
	sem_wait(philo->data->death);
	philo->last_meal = get_time(philo->data) -
	philo->data->start_simulation;
	sem_post(philo->data->death);
	(philo->eat_counter > -1) ? philo->eat_counter-- : 0;
}

char	*ft_create_str(int philo, char *str)
{
	char	*res;
	char	*num;
	int		i;
	int		j;

	i = 1;
	j = 0;
	num = ft_itoa(philo);
	res = (char*)malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(num) + 2));
	res[0] = ' ';
	while (num[j])
	{
		res[i] = num[j];
		j++;
		i++;
	}
	while (*str)
	{
		res[i] = *str++;
		i++;
	}
	res[i] = '\0';
	free(num);
	return (res);
}

void	fill_data(t_data *data)
{
	sem_t		*dead;
	sem_t		*output;
	sem_t		*wait;
	sem_t		*time;

	sem_unlink("output");
	sem_unlink("dead");
	sem_unlink("wait");
	sem_unlink("time");
	output = sem_open("output", O_CREAT, S_IRWXU, 1);
	dead = sem_open("dead", O_CREAT, S_IRWXU, 1);
	wait = sem_open("wait", O_CREAT, S_IRWXU, 1);
	time = sem_open("time", O_CREAT, S_IRWXU, 1);
	data->output = output;
	data->death = dead;
	data->wait = wait;
	data->time = time;
}
