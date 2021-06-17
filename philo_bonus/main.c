/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:49:03 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/17 15:03:15 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*checker(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(2000);
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

void	*fork_you(t_philo *philo)
{
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

void	init_process(t_data *data, pthread_t *monitor)
{
	int	*pid;
	int	n;

	pid = malloc(sizeof(int) * data->nb);
	n = data->nb;
	while (--n >= 0)
	{
		data->philo[n].meal = data->meals;
		data->philo[n].i = n;
		pid[n] = fork();
		if (pid[n] == 0)
		{
			pthread_create(&monitor[n], NULL, checker, &data->philo[n]);
			fork_you(&data->philo[n]);
		}
		else if (pid[n] == -1)
		{
			printf("Error\nProcess creation failed\n");
			exit(1);
		}
	}
	pthread_mutex_lock(&data->dead);
	free(pid);
	exit(0);
}

int	check_arg(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		if (ft_isnotnum(av[i]))
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	*monitor;

	if (ac < 5 || ac > 6)
		return (0);
	if (check_arg(av))
		return (0);
	data.nb = ft_atoi(av[1]);
	monitor = malloc(sizeof(pthread_t) * data.nb);
	if (!monitor)
		return (1);
	pthread_mutex_lock(&data.dead);
	ft_init(&data, av, ac);
	ft_init_philo(&data, data.nb);
	init_sem(&data);
	init_process(&data, monitor);
	usleep(100);
	return (0);
}
