/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:07:18 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/13 15:41:46 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{	
		if (s1[i] != s2[i])
		{
			if (s1[i] < 0)
				return (s2[i] - s1[i]);
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

void	print(t_philo *philo, char *action)
{
	int	time;
	int	nb;

	time = get_time() - read_value(&philo->start, &philo->access);
	nb = read_value(&philo->nb, &philo->access);
	pthread_mutex_lock(&philo->args->death);
	pthread_mutex_lock(&philo->args->print);
	if (!philo->args->dead)
	{
		if (!ft_strncmp(action, "has died", 9))
			philo->args->dead = 1;
		printf("%d	%d %s\n", time, nb, action);
	}
	pthread_mutex_unlock(&philo->args->print);
	pthread_mutex_unlock(&philo->args->death);
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
	t_philo		*philo;

	philo = (t_philo *)phi;
	if (read_value(&philo->nb, &philo->access) % 2 == 0)
		ft_usleep(read_value(&philo->tte, &philo->access), philo);
	while (!read_value(&philo->args->dead, &philo->args->death))
	{
		meal(philo);
		print(philo, "is sleeping");
		ft_usleep(philo->tts, philo);
		print(philo, "is thinking");
	}
	return (NULL);
}
