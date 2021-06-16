/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:49:03 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/16 18:01:17 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

char	*get_m(int i)
{
	if (i == FORK)
		return(" has taken a fork\n");
	else if (i == EAT)
		return(" is eating\n");
	else if (i == SLEEP)
		return(" is sleeping\n");
	else if (i == THINK)
		return(" is thinking\n");
	else if (i == DIE)
		return(" die\n");
	else if (i == MEAL)
		return(" ate all meals\n");
	return (NULL);
}

void	send_m(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->display);
	printf("%llu %d%s", set_time() - philo->data->tod, philo->id, get_m(i));
	if (!(i == DIE || i == MEAL))
		pthread_mutex_unlock(&philo->data->display);
}

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
			break;
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

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	*philo;
	pthread_t	*monitor;
	int			n;
	int			meals;

	if (ac < 5 || ac > 6)
		return (1);
	n = ft_atoi(av[1]);
	philo = malloc(sizeof(pthread_t) * n);
	monitor = malloc(sizeof(pthread_t) * n);
	ft_init(&data, av);
	ft_init_philo(&data, n, data.nb);
	pthread_mutex_lock(&data.dead);
	if (ac == 6)
		meals = ft_atoi(av[5]);
	while (--n >= 0)
	{
		if (ac == 6)
			data.philo[n].meal = meals;
		data.philo[n].i = n;
		pthread_create(&philo[n], NULL, f1, &data.philo[n]);
		usleep(100);
		pthread_create(&monitor[n], NULL, checker, &data.philo[n]);

	}
	n = data.nb;
	pthread_mutex_lock(&data.dead);
	pthread_mutex_unlock(&data.dead);
	free_tab(monitor, philo, data.fork);
	return (0);
}