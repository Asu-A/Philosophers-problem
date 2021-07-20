#include "philo_two.h"

int		ft_intlen(int n)
{
	int	counter;

	counter = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

int		ft_num_itoa(int n, int len, int counter, int c)
{
	int divisor;
	int	num;

	divisor = 1;
	while (len-- - 1 > counter)
		divisor = divisor * 10;
	if (c == 1)
		num = n / divisor;
	else
		num = n % divisor;
	return (num);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;
	int		counter;

	len = ft_intlen(n);
	res = (char*)malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	counter = -1;
	while (++counter < len)
	{
		res[counter] = (ft_num_itoa(n, len, counter, 1)) + '0';
		n = ft_num_itoa(n, len, counter, 2);
	}
	res[counter] = '\0';
	return (res);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		counter;
	int		index;

	counter = 0;
	index = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	res = (char*)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (s1[index] != '\0')
		res[counter++] = s1[index++];
	free(s1);
	index = 0;
	while (s2[index] != '\0')
		res[counter++] = s2[index++];
	res[counter] = '\0';
	return (res);
}
