/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:48:39 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/01 20:06:40 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_brain	brain;
	t_philo	**philosophers;

	if (argc < 5 || argc > 6)
		return (1);
	if (check_args(argv))
		return (1);
	init_brain(argv, &brain);
	init_philo(&philosophers, &brain);
	return (0);
}
