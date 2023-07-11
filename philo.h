/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:50:19 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/11 18:02:03 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct s_brain
{
	int				min_meal;
	int				meals;
	int				nb_philo;
	int				dead;
	pthread_mutex_t	*fks;
	pthread_mutex_t	access;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}	t_brain;

typedef struct s_philo
{
	int				nb;
	int				tte;
	int				tts;
	int				ttd;
	int				meals;
	int				last_meal;
	int				start;
	t_brain			*args;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	access;
}	t_philo;

int		ft_atoi(const char *str, int *error);
int		check_args(char **argv);
void	init_brain(char **argv, t_brain *brain);
void	mutex_init(t_brain *brain);
int		get_time(void);
void	*life(void *philo);
int		init_philo(t_philo **phi, t_brain *brain, char **av);
void	*ft_calloc(size_t nmemb, size_t size);
int		read_value(int *value, pthread_mutex_t *mutex);
void	ft_usleep(int time, t_philo *philo);
void	*check_death(void *ph);
void	print(t_philo *philo, char *action);

#endif