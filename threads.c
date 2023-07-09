/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:18 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/09 02:37:55 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_value(int *value, pthread_mutex_t *mutex)
{
	int	rv;

	pthread_mutex_lock(mutex);
	rv = *value;
	pthread_mutex_unlock(mutex);
	return (rv);
}

void	ft_usleep(int time, t_philo *philo)
{
	int	start;
	int	dead;	

	start = get_time();
	dead = read_value(&philo->args->dead, &philo->args->access);
	while (get_time() - start < time && !dead)
	{
		usleep(100);
		check_death(philo);
		dead = read_value(&philo->args->dead, &philo->args->access);
	}
}

void	ft_eat(t_philo *philo)
{
	int	temp_time;

	if (read_value(&philo->args->dead, &philo->args->access))
		return ;
	pthread_mutex_lock(&philo->args->access);
	temp_time = philo->args->start;
	pthread_mutex_unlock(&philo->args->access);
	pthread_mutex_lock(philo->fork_r);
	printf("%d %d has taken a fork\n", get_time() - temp_time, philo->nb);
	pthread_mutex_lock(philo->fork_l);
	printf("%d %d has taken a fork\n", get_time() - temp_time, philo->nb);
	printf("%d %d is eating\n", get_time() - temp_time, philo->nb);
	philo->last_meal = get_time();
	ft_usleep(philo->tte, philo);
	philo->meals++;
	pthread_mutex_lock(&philo->args->access);
	if (philo->meals == philo->args->min_meal)
		philo->args->meals++;
	pthread_mutex_unlock(&philo->args->access);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
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
		ft_eat(philo);
		check_death(philo);
		if (read_value(&philo->args->dead, &philo->args->access))
			return (NULL);
		printf("%d %d is sleeping\n", get_time() - temp_time, philo->nb);
		ft_usleep(philo->tts, philo);
		check_death(philo);
		if (read_value(&philo->args->dead, &philo->args->access))
			return (NULL);
		printf("%d %d is thinking\n", get_time() - temp_time, philo->nb);
	}
	return (NULL);
}
