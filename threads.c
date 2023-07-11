/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:18 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/11 15:51:01 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *action)
{
	int	time;
	int	nb;

	time = get_time() - read_value(&philo->args->start, &philo->args->access);
	nb = read_value(&philo->nb, &philo->access);
	pthread_mutex_lock(&philo->args->print);
	if (!read_value(&philo->args->dead, &philo->args->access))
		printf("%d	%d %s\n", time, nb, action);
	pthread_mutex_unlock(&philo->args->print);
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
	pthread_mutex_lock(&philo->args->access);
	pthread_mutex_lock(&philo->access);
	philo->meals++;
	if (philo->meals == philo->args->min_meal)
		philo->args->meals++;
	pthread_mutex_unlock(&philo->args->access);
	pthread_mutex_unlock(&philo->access);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	*life(void *phi)
{
	int			temp_time;
	t_philo		*philo;
	pthread_t	death;

	pthread_create(&death, NULL, &check_death, phi);
	philo = (t_philo *)phi;
	temp_time = read_value(&philo->args->start, &philo->args->access);
	if (read_value(&philo->nb, &philo->access) % 2 == 0)
		ft_usleep(read_value(&philo->tte, &philo->access), philo);
	while (!read_value(&philo->args->dead, &philo->args->access))
	{
		meal(philo);
		print(philo, "is sleeping");
		ft_usleep(philo->tts, philo);
		print(philo, "is thinking");
	}
	pthread_join(death, NULL);
	return (NULL);
}
