/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:24:18 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/17 15:03:03 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_init(t_data *data, char **av, int ac)
{
	int	nb;

	nb = data->nb;
	data->tod = set_time();
	data->philo = malloc(sizeof(t_philo) * nb);
	data->tte = ft_atoi(av[3]);
	data->tts = ft_atoi(av[4]);
	data->ttt = 0;
	data->ttd = ft_atoi(av[2]);
	data->meals = -1;
	if (ac == 6)
		data->meals = ft_atoi(av[5]);
}

void	ft_init_philo(t_data *data, int n)
{
	while (--n >= 0)
	{
		data->philo[n].meal = -1;
		data->philo[n].eat = 0;
		data->philo[n].data = data;
		data->philo[n].id = n + 1;
	}
}

int	ft_isnotnum(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] < '0' || s[i] > '9')
			return (1);
	return (0);
}

void	init_sem(t_data *data)
{
	sem_t	*sem;
	int		valeur;

	valeur = data->nb;
	sem = sem_open("philo", O_CREAT, S_IRWXU, valeur);
	if (sem == SEM_FAILED)
	{
		printf("sem_open failed\n");
		exit(EXIT_FAILURE);
	}
}
