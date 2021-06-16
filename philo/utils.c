/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:28:33 by kmacquet          #+#    #+#             */
/*   Updated: 2021/06/16 17:30:01 by kmacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

unsigned long long	set_time()
{
	struct timeval t_time;
	
	gettimeofday(&t_time, NULL);
	return (t_time.tv_sec * 1000 + t_time.tv_usec / 1000);
}

void	free_tab(pthread_t *philo, pthread_t *monitor, pthread_mutex_t *fork)
{
	free(philo);
	free(monitor);
	free(fork);
}