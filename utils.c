/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:43:58 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/11 13:29:28 by lvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str, int *error)
{
	int	nb;
	int	sign;
	int	temp;

	nb = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (is_digit(*str))
	{
		temp = nb;
		nb = nb * 10 + (*str++ - '0');
		if (nb < temp)
			*error = 1;
	}
	if (*str)
		*error = 1;
	return (nb * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*rv;

	if (nmemb > 0xFFFFFFFFUL || size > 0xFFFFFFFFUL)
		return (NULL);
	if (nmemb * size > 0xFFFFFFFFUL)
		return (NULL);
	rv = malloc(nmemb * size);
	if (!rv)
		return (NULL);
	else
	{
		memset(rv, 0, nmemb * size);
		return (rv);
	}
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int time, t_philo *philo)
{
	int	start;
	int	dead;	

	start = get_time();
	dead = read_value(&philo->args->dead, &philo->args->access);
	while (get_time() - start < time && !dead)
	{
		usleep(100);
		dead = read_value(&philo->args->dead, &philo->args->access);
	}
}
