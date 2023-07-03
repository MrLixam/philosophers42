/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:18 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/03 22:54:24 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time, t_philo *philo)
{
	int	start;	

	start = get_time();
	while (get_time() - start < time && !philo->args->dead)
		usleep(10);
}

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
	if (philo->nb % 2)
		ft_usleep(philo->tts, philo);
	while (!dead)
	{
		ft_eat(philo);
		dead = read_value(philo->args->dead, philo->args->death);
		
	}
}
