/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvincent <lvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:43:58 by lvincent          #+#    #+#             */
/*   Updated: 2023/07/01 20:14:38 by lvincent         ###   ########.fr       */
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
	while (*str >= 9 && *str <= 13 || *str == ' ')
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
		ft_bzero(rv, nmemb * size);
		return (rv);
	}
}
