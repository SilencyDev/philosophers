/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:46:55 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/16 20:00:31 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define MEAL 5

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					i;
	int					eat;
	unsigned long long	ta;
	int					meal;
	t_data				*data;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
}						t_philo;

typedef struct s_data
{
	int					meals;
	pthread_mutex_t		dead;
	pthread_mutex_t		display;
	int					stop;
	int					nb;
	unsigned long long	tod;
	unsigned long long	tte;
	unsigned long long	tts;
	unsigned long long	ttt;
	unsigned long long	ttd;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}						t_data;

void				ft_init(t_data *data, char **av, int ac);
void				ft_init_philo(t_data *data, int n, int nb);
void				fork_on(t_philo *philo);
void				eat_on(t_philo *philo);
void				fork_off(t_philo *philo);
void				sleep_on(t_philo *philo);
int					ft_atoi(char *str);
unsigned long long	set_time(void);
void				free_tab(pthread_t *philo, pthread_t *monitor,
						pthread_mutex_t *fork);
void				send_m(t_philo *philo, int i);
char				*get_m(int i);
void				*checker(void *arg);
int					ft_isnotnum(char *s);

#endif