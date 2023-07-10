/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 03:55:45 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/10 17:56:12 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **argv)
{
	int	i;
	int	error;
	int	temp;

	i = 0;
	while (argv[++i])
	{
		temp = ft_atoi(argv[i], &error);
		if (temp < 0)
			error = 1;
	}
	return (error);
}

void	init_brain(char **argv, t_brain *brain)
{
	int				i;
	struct timeval	t;

	i = -1;
	brain->nb_philo = ft_atoi(argv[1], &i);
	brain->min_meal = -1;
	if (argv[5])
		brain->min_meal = ft_atoi(argv[5], &i);
	brain->meals = 0;
	gettimeofday(&t, NULL);
	brain->start = t.tv_sec * 1000 + t.tv_usec / 1000;
	mutex_init(brain);
}

int	init_philo(t_philo **philo, t_brain *brain, char **av)
{
	int		i;
	int		error;
	t_philo	*phi;

	i = -1;
	*philo = (t_philo *)ft_calloc(brain->nb_philo, sizeof(t_philo));
	phi = *philo;
	if (!phi)
		return (1);
	while (++i < brain->nb_philo)
	{
		phi[i].nb = i + 1;
		phi[i].args = brain;
		phi[i].fork_r = &brain->fks[i];
		phi[i].fork_l = &brain->fks[(i + 1) % brain->nb_philo];
		phi[i].ttd = ft_atoi(av[2], &error);
		phi[i].tte = ft_atoi(av[3], &error);
		phi[i].tts = ft_atoi(av[4], &error);
		phi[i].last_meal = brain->start;
		pthread_mutex_init(&phi[i].access, NULL);
	}
	return (0);
}

void	mutex_init(t_brain *b)
{
	int	i;

	i = -1;
	pthread_mutex_init(&b->access, NULL);
	b->fks = (pthread_mutex_t *)ft_calloc(b->nb_philo, sizeof(pthread_mutex_t));
	if (!(b->fks))
		return ;
	while (++i < b->nb_philo)
		pthread_mutex_init(&b->fks[i], NULL);
}	
