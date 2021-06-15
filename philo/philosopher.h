/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:46:55 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/14 18:30:58 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int				alive;
	int				id;
	int				i;
	t_data			*data;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}				t_philo;

typedef struct s_data
{
	int					nb;
	unsigned long long	tod;
	unsigned long long	tte;
	unsigned long long	tts;
	unsigned long long	ttt;
	unsigned long long	ttd;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}				t_data;
#endif