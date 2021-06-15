/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:49:03 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/15 07:07:21 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*f1(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(philo->rfork);
	printf("%d is eating\n", philo->id);
	usleep(philo->data->tte);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	printf("%d is sleeping\n", philo->id);
	usleep(philo->data->tts);
	printf("%d is thinking\n", philo->id);
	pthread_exit(NULL);
}

// void	*f2(void *arg)
// {
// 	(void)arg;
// 	printf("Thread 2\n");
// 	pthread_exit(NULL);
// }

int	ft_atoi(char *str)
{
	unsigned int	i;
	int				posneg;
	int				result;

	i = 0;
	result = 0;
	posneg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			posneg = -1;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	return (result * posneg);
}

void	ft_init(t_data *data, char **av)
{
	int	nb;

	nb = ft_atoi(av[1]);
	data->nb = nb;
	data->fork = malloc(sizeof(pthread_mutex_t) * nb);
	data->philo = malloc(sizeof(t_philo) * nb);
	while (--nb >= 0)
		pthread_mutex_init(&data->fork[nb], NULL);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	data->ttt = 0;
	data->ttd = ft_atoi(av[2]);
}

void	ft_init_philo(t_data *data, int n, int nb)
{
	while (--n >= 0)
	{
		data->philo[n].alive = 1;
		data->philo[n].data = data;
		data->philo[n].id = n + 1;
		data->philo[n].rfork = &data->fork[n];
		if (n - 1 < 0)
			data->philo[n].lfork = &data->fork[nb - 1];
		else
			data->philo[n].lfork = &data->fork[n - 1];
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	*t;
	int			n;

	if (ac != 5)
		return (1);
	n = ft_atoi(av[1]);
	t = malloc(sizeof(pthread_t) * n);
	ft_init(&data, av);
	ft_init_philo(&data, n, data.nb);
	while (--n >= 0)
	{
		data.philo[n].i = n;
		pthread_create(&t[n], NULL, f1, &data.philo[n]);
	}
	n = data.nb;
	while (--n >= 0)
	{
		pthread_join(t[n], NULL);
	}
	return (0);
}