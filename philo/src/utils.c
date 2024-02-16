/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:47:45 by castorga          #+#    #+#             */
/*   Updated: 2024/02/15 19:37:28 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_msgs(t_philo *ph, char *msg)
{
	if (get_its_alive(ph->pchrono_ph))
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u %s\n", get_current_time(ph->pchrono_ph), \
		ph->num_ph, msg);
		pthread_mutex_unlock(&ph->mutex_msgs);
		return ;
	}
}

/*Destroys the resources used by a t_chrono object*/
int	destroy(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		pthread_mutex_destroy(&ch->pforks[i]);
		i++;
	}
	free(ch->pforks);
	free(ch->pph);
	pthread_mutex_destroy(&ch->pph->mutex_last_eat);
	pthread_mutex_destroy(&ch->mutex_times);
	return (0);
}

long	ft_atol2(const char *str, long res, int sign, int i)
{
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
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	ft_atol2(str, res, sign, i);
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
