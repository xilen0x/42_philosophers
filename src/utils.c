/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:47:45 by castorga          #+#    #+#             */
/*   Updated: 2024/02/08 19:22:04 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Destroys the resources used by a t_chrono object*/
int	destroy(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		//pthread_mutex_destroy(&ch->pph[i].mutex_nbr_of_meals);
		pthread_mutex_destroy(&ch->pph[i].mutex_last_eat);
		pthread_mutex_destroy(&ch->pforks[i]);
		i++;
	}
	free(ch->pforks);
	free(ch->pph);
	pthread_mutex_destroy(&ch->mutex_its_alive);
	pthread_mutex_destroy(&ch->mutex_msgs);
	return (0);
}

/*Converts a string to a long number, disregarding spaces and 
considering signs.*/
long	ft_atol(const char *str)
{
	int		i;
	int		neg;
	long	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * neg);
}

/*Checks if a character is a digit (0-9).*/
int	ft_isdigit(char num)
{
	if (num >= '0' && num <= '9')
	{
		return (1);
	}
	return (0);
}

/*Checks if a string contains at least one digit.*/
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
