/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:18 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/10 18:34:00 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *action)
{
	int	time;

	pthread_mutex_lock(&philo->access);
	time = get_time() - read_value(&philo->args->start, &philo->args->access);
	if (!read_value(&philo->args->dead, &philo->args->access))
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

void	meal(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	print(philo, "has taken a fork");
	if (read_value(&philo->args->nb_philo, &philo->args->access) == 1)
	{
		ft_usleep(read_value(&philo->ttd, &philo->access) * 2, philo);
		pthread_mutex_unlock(philo->fork_l);
		return ;
	}
	pthread_mutex_lock(philo->fork_r);
	print(philo, "has taken a fork");
	print(philo, "is eating");
	pthread_mutex_lock(&philo->access);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->access);
	ft_usleep(read_value(&philo->tte, &philo->access), philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_lock(&philo->access);
	philo->meals++;
	philo->args->meals++;
	pthread_mutex_unlock(&philo->access);
}

void	*life(void *phi)
{
	int			temp_time;
	t_philo		*philo;
	pthread_t	death;

	pthread_create(&death, NULL, &check_death, phi);
	pthread_detach(death);
	philo = (t_philo *)phi;
	temp_time = read_value(&philo->args->start, &philo->args->access);
	if (read_value(&philo->nb, &philo->access) % 2 == 0)
		ft_usleep(read_value(&philo->tte, &philo->access), philo);
	while (1)
	{
		meal(philo);
		print(philo, "is sleeping");
		ft_usleep(philo->tts, philo);
		print(philo, "is thinking");
	}
	return (NULL);
}
