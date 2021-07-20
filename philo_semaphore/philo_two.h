#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/stat.h>

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
	sem_t			*output;
	sem_t			*death;
	sem_t			*wait;
	sem_t			*time;
}					t_data;

typedef struct		s_philo
{
	pthread_t		*threads;
	sem_t			*forks;
	pthread_t		*death;
	int				index;
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
void				drop_forks(t_philo *philo);
void				take_forks(t_philo *philo);
int					ft_parser(char *argv[], t_data *data, int argc);
int					my_sleep(long timer, t_data *data);
long				get_time(t_data *data);
int					ft_print(t_philo *philo, char *str);
void				ft_init_philo(t_philo *philo, t_data *data, int i);
void				ft_join_treads(pthread_t *death,
						pthread_t *threads, int counter, t_data *data);
void				fill_data(t_data *data);
char				*ft_create_str(int philo, char *str);
void				change_last_meal(t_philo *philo);
void				ft_death_helper(t_philo *philo, char *str);

#endif
