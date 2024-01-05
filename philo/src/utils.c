/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:47:45 by castorga          #+#    #+#             */
/*   Updated: 2024/01/04 12:47:47 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#include <limits.h>

long	ft_atol(const char *str)
{
	int i;
	long res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LONG_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}


int	ft_isdigit(char num)
{
	if (num >= '0' && num <= '9')
	{
		return (1);
	}
	return (0);
}

int	contains_digit(char *c)
{
	while (*c)
	{
		if (ft_isdigit(*c) && *c != ' ' && *c != '\"')
			return (1);
		c++;
	}
	return (0);
}

/*obtener el tiempo total en milisegundos*/
long long	get_time(void)
{
	struct timeval	info_time;

	gettimeofday(&info_time, NULL);
	return (info_time.tv_sec * 1000 + info_time.tv_usec / 1000);
}
