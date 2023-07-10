/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:48:39 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/10 02:11:50 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_brain *brain)
{
	int	time;

	time = get_time();
	if (time - philo->last_meal >= philo->ttd)
	{
		pthread_mutex_lock(&philo->args->access);
		print(philo, time - philo->args->start, "died");
		philo->args->dead = 1;
		pthread_mutex_unlock(&philo->args->access);
		return (1);
	}
	pthread_mutex_lock(&philo->args->access);
	if (philo->args->meals >= philo->args->nb_philo
		&& philo->args->min_meal != -1)
		philo->args->dead = 1;
	pthread_mutex_unlock(&philo->args->access);
	return (read_value(&brain->dead, &brain->access));
}

void	manager(t_philo *philo, t_brain *brain)
{
	int	i;
	int	end;

	while (1)
	{
		i = -1;
		while (++i < read_value(&brain->nb_philo, &brain->access))
		{
			end = check_death(&philo[i], brain);
			if (end)
				return ;
		}
	}
}

void	free_all(t_philo *philosophers, t_brain *brain, pthread_t *th)
{
	int	i;

	i = -1;
	while (++i < read_value(&brain->nb_philo, &brain->access))
		pthread_join(th[i], NULL);
	i = -1;
	while (++i < brain->nb_philo)
	{
		pthread_mutex_destroy(&brain->fks[i]);
		pthread_mutex_destroy(&philosophers[i].access);
	}
	if (philosophers)
		free(philosophers);
	if (th)
		free(th);
}

void	ft_error(t_philo *philosophers, t_brain *brain, pthread_t *th)
{
	write(2, "Error\n", 6);
	free_all(philosophers, brain, th);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_brain		brain;
	t_philo		*philosophers;
	pthread_t	*threads;
	int			error;
	int			i;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_args(argv))
		return (1);
	init_brain(argv, &brain);
	error = init_philo(&philosophers, &brain, argv);
	if (error)
		ft_error(philosophers, &brain, NULL);
	threads = (pthread_t *)ft_calloc(brain.nb_philo, sizeof(pthread_t));
	if (!threads)
		ft_error(philosophers, &brain, threads);
	i = -1;
	while (++i < brain.nb_philo)
		pthread_create(&threads[i], NULL, life, &philosophers[i]);
	i = -1;
	manager(philosophers, &brain);
	free_all(philosophers, &brain, threads);
	return (0);
}
