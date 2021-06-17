/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:22:34 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/17 14:48:21 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	fork_on(t_philo *philo)
{
	sem_wait(philo->data->sem);
	send_m(philo, FORK);
	sem_wait(philo->data->sem);
	send_m(philo, FORK);
}

void	eat_on(t_philo *philo)
{
	philo->eat = 1;
	philo->ta = set_time();
	send_m(philo, EAT);
	usleep(philo->data->tte * 1000);
}

void	fork_off(t_philo *philo)
{
	sem_post(philo->data->sem);
	sem_post(philo->data->sem);
	philo->eat = 0;
}

void	sleep_on(t_philo *philo)
{
	send_m(philo, SLEEP);
	usleep(philo->data->tts * 1000);
}
