/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:48:39 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/10 19:01:13 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *ph)
{
	t_philo	*p;
	t_brain	brain;

	p = (t_philo *)ph;
	brain = *p->args;
	while (1)
	{
		pthread_mutex_lock(&brain.access);
		if (get_time() - read_value(&p->last_meal, &p->access)
			> read_value(&p->ttd, &p->access))
		{
			if (!brain.dead)
				printf("%d %d died\n", get_time() - brain.start,
					read_value(&p->nb, &p->access));
			brain.dead = 1;
		}
		if (brain.meals >= brain.nb_philo && brain.min_meal != -1)
			brain.dead = 1;
		pthread_mutex_unlock(&brain.access);
		if (read_value(&brain.dead, &brain.access))
			return (NULL);
		usleep(1000);
	}
}

void	free_all(t_philo *philosophers, t_brain *brain, pthread_t *th)
{
	int	i;

	pthread_mutex_destroy(&brain->access);
	i = -1;
	while (++i < brain->nb_philo)
		pthread_mutex_destroy(&brain->fks[i]);
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

	if ((argc < 5 || argc > 6) || check_args(argv))
		return (1);
	init_brain(argv, &brain);
	error = init_philo(&philosophers, &brain, argv);
	threads = (pthread_t *)ft_calloc(brain.nb_philo, sizeof(pthread_t));
	if (!threads || error)
		ft_error(philosophers, &brain, threads);
	i = -1;
	pthread_mutex_lock(&brain.access);
	while (++i < brain.nb_philo)
		pthread_create(&threads[i], NULL, life, &philosophers[i]);
	pthread_mutex_unlock(&brain.access);
	i = -1;
	while (++i < brain.nb_philo)
		pthread_join(threads[i], NULL);
	free_all(philosophers, &brain, threads);
	return (0);
}
