/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:49:03 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/16 18:37:05 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*checker(void *arg)
{
	t_philo	*philo;
	int		n;

	philo = (t_philo *)arg;
	n = philo->data->nb;
	while (1)
	{
		if ((!philo->eat && set_time() - philo->ta > philo->data->ttd)
			|| philo->meal == 0)
		{
			if (philo->meal == 0)
				send_m(philo, MEAL);
			else
				send_m(philo, DIE);
			pthread_mutex_unlock(&philo->data->dead);
			break ;
		}
	}
	return (NULL);
}

void	*f1(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->ta = set_time();
	while (1)
	{
		fork_on(philo);
		eat_on(philo);
		fork_off(philo);
		if (philo->meal > 0)
			--philo->meal;
		sleep_on(philo);
		send_m(philo, THINK);
	}
	return ((void *)"die");
}

void	init_threads(t_data *data, pthread_t *philo, pthread_t *monitor)
{
	int	n;

	n = data->nb;
	while (--n >= 0)
	{
		data->philo[n].meal = data->meals;
		data->philo[n].i = n;
		pthread_create(&philo[n], NULL, f1, &data->philo[n]);
		usleep(100);
		pthread_create(&monitor[n], NULL, checker, &data->philo[n]);
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	*philo;
	pthread_t	*monitor;

	if (ac < 5 || ac > 6)
		return (1);
	data.nb = ft_atoi(av[1]);
	philo = malloc(sizeof(pthread_t) * data.nb);
	monitor = malloc(sizeof(pthread_t) * data.nb);
	ft_init(&data, av, ac);
	ft_init_philo(&data, data.nb, data.nb);
	pthread_mutex_lock(&data.dead);
	init_threads(&data, philo, monitor);
	pthread_mutex_lock(&data.dead);
	pthread_mutex_unlock(&data.dead);
	free_tab(monitor, philo, data.fork);
	return (0);
}
