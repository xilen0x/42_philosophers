/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/01/23 19:07:23 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ph_msgs(t_philo *ph, int n)
{
	pthread_mutex_lock(&ph->mutex_msgs);
	if (n == FORK)
		printf("%lld %u has taken a fork\n", \
		difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	else if (n == EAT)
		printf("%lld %u is eating\n", \
		difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	else if (n == SLEEP)
		printf("%lld %u is sleeping\n", \
		difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	else if (n == THINK)
		printf("%lld %u is thinking\n", \
		difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	else if (n == DIE)
		printf("%lld %u died\n", \
		difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	pthread_mutex_unlock(&ph->mutex_msgs);
}

void	ph_sleep(long long time)
{
	long long	cu_time;

	cu_time = get_time();
	while (1)
	{
		if (difference_of_time(cu_time, get_time()) >= time)
			break ;
		usleep(1000);
	}
}

static void	set_last_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_last_eat);
	ph->last_eat = get_time();
	pthread_mutex_unlock(&ph->mutex_last_eat);
}

static void	set_number_of_meals(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_nbr_of_meals);
	ph->number_of_meals++;
	pthread_mutex_unlock(&ph->mutex_nbr_of_meals);
}

void	ph_eats(t_philo *ph)
{
	pthread_mutex_lock(ph->mutex_left_fork);
	ph_msgs(ph, FORK);//aki voy... rama dev - Cuando es un philosofo, Como sabe si hay o no un fork disponible? 
	pthread_mutex_lock(ph->mutex_right_fork);
	ph_msgs(ph, FORK);
	ph_msgs(ph, EAT);
	set_last_eat(ph);
	ph_sleep(ph->chrono_ph->time_to_eat);
	set_number_of_meals(ph);
	pthread_mutex_unlock(ph->mutex_left_fork);
	pthread_mutex_unlock(ph->mutex_right_fork);
}
