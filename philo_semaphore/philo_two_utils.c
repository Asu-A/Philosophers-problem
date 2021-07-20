#include "philo_two.h"

int		ft_strncmp(const char *str1, const char *str2, int n)
{
	int				counter;
	unsigned char	*s1;
	unsigned char	*s2;

	counter = 0;
	s1 = (unsigned char*)str1;
	s2 = (unsigned char*)str2;
	while (counter < n)
	{
		if (s1[counter] == '\0' && s2[counter] == '\0')
			break ;
		else if (s1[counter] == s2[counter])
			counter++;
		else
			return (s1[counter] - s2[counter]);
	}
	return (0);
}

int		ft_error_msg(char *str, int len)
{
	write(1, str, len);
	return (-1);
}

int		ft_num(char *str)
{
	int num;

	num = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			num = num * 10 + (*str - '0');
		else
			return (ft_error_msg("Arguments must be numbers\n", 26));
		str++;
	}
	return (num);
}

int		ft_num_len(int num)
{
	int i;

	i = 0;
	if (num == 0)
		i = 1;
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

void	ft_death_helper(t_philo *philo, char *str)
{
	sem_wait(philo->data->output);
	sem_wait(philo->data->death);
	(philo->data->dead_flag2 != 1) ? write(1, str, ft_strlen(str)) : 0;
	drop_forks(philo);
	philo->data->dead_flag2 = 1;
	sem_post(philo->data->death);
	sem_post(philo->data->output);
}
