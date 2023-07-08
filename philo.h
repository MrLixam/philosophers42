/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:50:19 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/08 22:18:17 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_brain
{
	int				min_meal;
	int				meals;
	int				nb_philo;
	int				dead;
	int				start;
	pthread_mutex_t	**fks;
	pthread_mutex_t	*access;
	pthread_mutex_t	*death;
}	t_brain;

typedef struct s_philo
{
	size_t			nb;
	int				tte;
	int				tts;
	int				ttd;
	int				meals;
	size_t			last_meal;
	t_brain			*args;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*self;
}	t_philo;

int		ft_atoi(const char *str, int *error);
int		check_args(char **argv);
void	init_brain(char **argv, t_brain *brain);
void	mutex_init(t_brain *brain);
int		get_time(void);
void	life(void *philo);

#endif