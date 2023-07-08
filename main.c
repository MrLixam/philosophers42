/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:48:39 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/08 22:17:30 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo **philosophers, t_brain *brain)
{
	int	i;

	i = 0;
	while (++i <= brain->nb_philo)
	{
		pthread_join((*philosophers)[i].thread, NULL);
		pthread_mutex_destroy((*philosophers)[i].self);
	}
	pthread_mutex_destroy(brain->access);
	pthread_mutex_destroy(brain->death);
	i = -1;
	while (++i < brain->nb_philo)
		pthread_mutex_destroy(brain->fks[i]);
}

void	ft_error(t_philo **philosophers, t_brain *brain)
{
	write(2, "Error\n", 6);
	free_all(philosophers, brain);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_brain	brain;
	t_philo	**philosophers;
	int		error;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_args(argv))
		return (1);
	init_brain(argv, &brain);
	error = init_philo(&philosophers, &brain);
	if (error)
		ft_error(philosophers, &brain);
	return (0);
}
