/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:18 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/16 18:37:37 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_init(t_data *data, char **av, int ac)
{
	int	nb;

	nb = data->nb;
	data->tod = set_time();
	data->fork = malloc(sizeof(pthread_mutex_t) * nb);
	data->philo = malloc(sizeof(t_philo) * nb);
	while (--nb >= 0)
		pthread_mutex_init(&data->fork[nb], NULL);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	data->ttt = 0;
	data->ttd = ft_atoi(av[2]);
	data->meals = -1;
	if (ac == 6)
		data->meals = ft_atoi(av[5]);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->display, NULL);
}

void	ft_init_philo(t_data *data, int n, int nb)
{
	while (--n >= 0)
	{
		data->philo[n].meal = -1;
		data->philo[n].eat = 0;
		data->philo[n].data = data;
		data->philo[n].id = n + 1;
		data->philo[n].lfork = &data->fork[n];
		if (n - 1 < 0)
			data->philo[n].rfork = &data->fork[nb - 1];
		else
			data->philo[n].rfork = &data->fork[n - 1];
	}
}
