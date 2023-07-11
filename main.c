/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:48:39 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/11 18:19:12 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_amount(t_brain *brain)
{
	pthread_mutex_lock(&brain->access);
	if (brain->meals >= brain->nb_philo && brain->min_meal != -1)
	{
		pthread_mutex_unlock(&brain->access);
		pthread_mutex_lock(&brain->death);
		brain->dead = 1;
		pthread_mutex_unlock(&brain->death);
	}
	else
		pthread_mutex_unlock(&brain->access);
}

void	*check_death(void *ph)
{
	int		val[3];
	t_philo	*p;
	t_brain	*brain;

	p = (t_philo *)ph;
	brain = p[0].args;
	val[1] = read_value(&brain->nb_philo, &brain->access);
	val[2] = read_value(&p[0].ttd, &p[0].access);
	while (1)
	{
		val[0] = -1;
		while (++val[0] < val[1])
		{
			if (get_time() - read_value(&p[val[0]].last_meal, \
				&p[val[0]].access) > val[2])
				if (!read_value(&brain->dead, &brain->death))
					print(&p[val[0]], "has died");
			check_amount(brain);
			if (read_value(&brain->dead, &brain->death))
				return (NULL);
		}
	}
}

void	free_all(t_philo *philosophers, t_brain *brain, pthread_t *th)
{
	int	i;

	pthread_mutex_destroy(&brain->access);
	pthread_mutex_destroy(&brain->print);
	pthread_mutex_destroy(&brain->death);
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
	pthread_t	supervisor;
	int			i;

	if ((argc < 5 || argc > 6) || check_args(argv))
		return (1);
	init_brain(argv, &brain);
	i = init_philo(&philosophers, &brain, argv);
	threads = (pthread_t *)ft_calloc(brain.nb_philo, sizeof(pthread_t));
	if (!threads || i)
		ft_error(philosophers, &brain, threads);
	i = -1;
	pthread_mutex_lock(&brain.access);
	while (++i < brain.nb_philo)
		pthread_create(&threads[i], NULL, life, &philosophers[i]);
	pthread_mutex_unlock(&brain.access);
	pthread_create(&supervisor, NULL, &check_death, philosophers);
	pthread_join(supervisor, NULL);
	i = -1;
	while (++i < read_value(&brain.nb_philo, &brain.access))
		pthread_join(threads[i], NULL);
	free_all(philosophers, &brain, threads);
	return (0);
}
