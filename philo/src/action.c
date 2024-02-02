/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/02/01 18:11:06 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_msgs(t_philo *ph, char *msg)//threads access
{
	if (ph->pchrono_ph->its_alive)
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u %s\n", diff_time(ph->pchrono_ph->start_time, get_time(ph->pchrono_ph)), ph->num_ph, msg);
		pthread_mutex_unlock(&ph->mutex_msgs);
		return ;
	}
	//pthread_mutex_unlock(&ph->mutex_msgs);
}

long long	get_last_eat(t_philo *ph)
{
	long long	last_eat;

	pthread_mutex_lock(&ph->mutex_last_eat);
	last_eat = ph->last_eat;
	pthread_mutex_unlock(&ph->mutex_last_eat);
	//printf("get_last_eat function\n");
	return (last_eat);
}

void	set_last_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_last_eat);
	ph->last_eat = get_time(ph->pchrono_ph);
	pthread_mutex_unlock(&ph->mutex_last_eat);
	//printf("set_last_eat function\n");
}

void	set_number_of_meals(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_nbr_of_meals);
	ph->number_of_meals++;
	pthread_mutex_unlock(&ph->mutex_nbr_of_meals);
	//printf("set_number_of_meals function\n");
}

void	ph_eats(t_philo *ph)
{
	pthread_mutex_lock(ph->pmutex_left_fork);
	ph_msgs(ph, "has taken a fork");
	pthread_mutex_lock(ph->pmutex_right_fork);
	ph_msgs(ph, "has taken a fork");
	pthread_mutex_lock(&ph->mutex_actions);
	ph_msgs(ph, "is eating");
	ph_eats_time(ph);
	set_last_eat(ph);
	set_number_of_meals(ph);
	ph_to_die_time(ph);
	pthread_mutex_unlock(&ph->mutex_actions);
	pthread_mutex_unlock(ph->pmutex_right_fork);
	pthread_mutex_unlock(ph->pmutex_left_fork);
	//printf("ph_eats function\n");
}
