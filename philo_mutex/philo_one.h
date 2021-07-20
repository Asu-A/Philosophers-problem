#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct		s_data
{
	int				counter;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_counter;
	int				dead_flag;
	int				dead_flag2;
	long			start_simulation;
	pthread_mutex_t	output;
	pthread_mutex_t	death;
	pthread_mutex_t	time;
}					t_data;

typedef struct		s_philo
{
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_t		*death;
	int				index;
	int				left_fork;
	int				right_fork;
	long			last_meal;
	int				eat_counter;
	t_data			*data;
}					t_philo;

char				*ft_itoa(int n);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strncmp(const char *str1, const char *str2, int n);
int					ft_num_len(int num);
int					ft_num(char *str);
int					ft_error_msg(char *str, int len);
void				drop_forks(t_philo *philo, int num);
void				take_forks(t_philo *philo, int num);
int					ft_parser(char *argv[], t_data *data, int argc);
int					my_sleep(long timer, t_data *data);
long				get_time(t_data *data);
int					ft_print(t_philo *philo, char *str);
void				ft_init_philo(t_philo *philo, t_data *data, int i);
void				ft_join_treads(pthread_t *death, pthread_t *threads,
						int counter);
char				*ft_create_str(int philo, char *str);
void				change_last_meal(t_philo *philo);
void				ft_create_treds(t_data *data, pthread_t
						*threads, pthread_t *death, t_philo *philo);
void				*ft_death(void *args);
void				*ft_simulation(void *args);
void				ft_death_helper(t_philo *philo, char *str);

#endif
