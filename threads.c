/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:18 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/08 22:20:38 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time, t_philo *philo)
{
	int	start;
	int	dead;	

	start = get_time();
	dead = read_value(philo->args->dead, philo->args->death);
	while (get_time() - start < time && !dead)
	{
		usleep(10);
		dead = read_value(philo->args->dead, philo->args->death);
	}
}

int	read_value(int value, pthread_mutex_t *mutex)
{
	int	rv;

	pthread_mutex_lock(mutex);
	rv = value;
	pthread_mutex_unlock(mutex);
	return (rv);
}

int	ft_eat(t_philo *philo)
{
	int	temp_time;

	if (read_value(philo->args->dead, philo->args->death))
		return (0);
	pthread_mutex_lock(philo->args->access);
	temp_time = philo->args->start;
	pthread_mutex_unlock(philo->args->access);
	pthread_mutex_lock(philo->self);
	pthread_mutex_lock(philo->fork_r);
	printf("%d %zu has taken a fork\n", get_time() - temp_time, philo->nb);
	pthread_mutex_lock(philo->fork_l);
	printf("%d %zu has taken a fork\n", get_time() - temp_time, philo->nb);
	printf("%d %zu is eating\n", get_time() - temp_time, philo->nb);
	philo->last_meal = get_time();
	ft_usleep(philo->tte, philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->self);
}

void	life(void *phi)
{
	int		temp_time;
	int		dead;
	t_philo	*philo;

	philo = (t_philo *)phi;
	temp_time = read_value(philo->args->start, philo->args->access);
	if (philo->nb % 2)
		ft_usleep(10, philo);
	dead = read_value(philo->args->dead, philo->args->death);
	while (!dead)
	{
		ft_eat(philo);
		if (read_value(philo->args->dead, philo->args->death))
			return ;
		pthread_mutex_lock(philo->self);
		printf("%d %zu is sleeping\n", get_time() - temp_time, philo->nb);
		pthread_mutex_unlock(philo->self);
		ft_usleep(philo->tts, philo);
		if (read_value(philo->args->dead, philo->args->death))
			return ;
		pthread_mutex_lock(philo->self);
		printf("%d %zu is thinking\n", get_time() - temp_time, philo->nb);
		pthread_mutex_unlock(philo->self);
		dead = read_value(philo->args->dead, philo->args->death);
	}
}
