#include "philo_one.h"

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
