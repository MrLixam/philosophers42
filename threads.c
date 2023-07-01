/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:18 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/01 21:12:16 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_value(int value, pthread_mutex_t *mutex)
{
	int	rv;

	pthread_mutex_lock(mutex);
	rv = value;
	pthread_mutex_unlock(mutex);
	return (rv);
}

void	life(t_philo *philo)
{
	int	dead;

	dead = read_value(philo->args->dead, philo->args->death);
	while (!dead)
	{
		dead = read_value(philo->args->dead, philo->args->death);
		if (philo->)
	}
}
