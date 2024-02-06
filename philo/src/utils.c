/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:47:45 by castorga          #+#    #+#             */
/*   Updated: 2024/02/06 10:34:43 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <limits.h>

int	destroy(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		pthread_mutex_destroy(&ch->pforks[i]);
		i++;
	}
	/*while (i < ch->q_philos)
	{
		pthread_join(ch->pph[i].thread, NULL);//JOIN<----
		i++;
	}*/
	free(ch->pforks);
	free(ch->pph);
	pthread_mutex_destroy(&ch->pph->mutex_last_eat);
	//pthread_mutex_destroy(&ch->pph->mutex_nbr_of_meals);
	//pthread_mutex_destroy(&ch->pph->mutex_msgs);
	//printf("llega aqui!!\n");
	//pthread_mutex_destroy(&ch->mutex_times);
	//pthread_mutex_destroy(&ch->mutex_its_alive);
	//pthread_mutex_destroy(&ch->pph->mutex_actions);
	return (0);
}

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
