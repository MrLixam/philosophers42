/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:18 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/10 02:36:56 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, int time, char *action)
{
	pthread_mutex_lock(&philo->access);
	printf("%d	%d %s\n", time, philo->nb, action);
	pthread_mutex_unlock(&philo->access);
}

int	read_value(int *value, pthread_mutex_t *mutex)
{
	int	rv;

	pthread_mutex_lock(mutex);
	rv = *value;
	pthread_mutex_unlock(mutex);
	return (rv);
}

void	eat(t_philo *philo)
{
	print(philo, get_time() - philo->args->start, "is eating");
	philo->last_meal = get_time();
	ft_usleep(read_value(&philo->tte, &philo->access), philo);
	pthread_mutex_lock(&philo->access);
	pthread_mutex_lock(&philo->args->access);
	philo->meals++;
	if (philo->args->min_meal != -1 && philo->meals == philo->args->min_meal)
		philo->args->meals++;
	pthread_mutex_unlock(&philo->args->access);
	pthread_mutex_unlock(&philo->access);
}

void	meal(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	print(philo, get_time() - philo->args->start, "has taken a fork");
	if (philo->args->nb_philo == 1)
	{	
		pthread_mutex_unlock(philo->fork_r);
		ft_usleep(philo->ttd, philo);
		return ;
	}
	pthread_mutex_lock(philo->fork_l);
	if (read_value(&philo->args->dead, &philo->args->access))
	{
		pthread_mutex_unlock(philo->fork_r);
		return ;
	}
	print(philo, get_time() - philo->args->start, "has taken a fork");
	if (read_value(&philo->args->dead, &philo->args->access))
	{
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		return ;
	}
	eat(philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	*life(void *phi)
{
	int		temp_time;
	t_philo	*philo;

	philo = (t_philo *)phi;
	temp_time = read_value(&philo->args->start, &philo->args->access);
	if (philo->nb % 2 == 0)
		ft_usleep(philo->tte, philo);
	while (!read_value(&philo->args->dead, &philo->args->access))
	{
		meal(philo);
		if (!read_value(&philo->args->dead, &philo->args->access))
			return (NULL);
		print(philo, get_time() - temp_time, "is sleeping");
		ft_usleep(philo->ttd, philo);
		if (!read_value(&philo->args->dead, &philo->args->access))
			return (NULL);
		print(philo, get_time() - temp_time, "is thinking");
	}
	return (NULL);
}
