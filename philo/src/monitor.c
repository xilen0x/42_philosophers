/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/01/25 13:19:42 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ph_msgs(t_philo *ph, int n)//threads access
{
	pthread_mutex_lock(&ph->mutex_msgs);
	if (n == FORK)
		printf("%lld %u has taken a fork\n", \
		difference_of_time(ph->pchrono_ph->start_time, get_time()), ph->num_ph);
	else if (n == EAT)
		printf("%lld %u is eating\n", \
		difference_of_time(ph->pchrono_ph->start_time, get_time()), ph->num_ph);
	else if (n == SLEEP)
		printf("%lld %u is sleeping\n", \
		difference_of_time(ph->pchrono_ph->start_time, get_time()), ph->num_ph);
	else if (n == THINK)
		printf("%lld %u is thinking\n", \
		difference_of_time(ph->pchrono_ph->start_time, get_time()), ph->num_ph);
	else if (n == DIE)
		printf("%lld %u died\n", \
		difference_of_time(ph->pchrono_ph->start_time, get_time()), ph->num_ph);
	pthread_mutex_unlock(&ph->mutex_msgs);
}

void	ph_sleep(long long time)//threads access
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

void	set_last_eat(t_philo *ph)//threads access
{
	pthread_mutex_lock(&ph->mutex_last_eat);
	ph->last_eat = get_time();
	pthread_mutex_unlock(&ph->mutex_last_eat);
}

void	set_number_of_meals(t_philo *ph)//threads access
{
	pthread_mutex_lock(&ph->mutex_nbr_of_meals);
	ph->number_of_meals++;
	pthread_mutex_unlock(&ph->mutex_nbr_of_meals);
}

void	ph_eats(t_philo *ph)//threads access
{
	pthread_mutex_lock(ph->pmutex_left_fork);
	ph_msgs(ph, FORK);
	pthread_mutex_lock(ph->pmutex_right_fork);
	ph_msgs(ph, FORK);

	set_last_eat(ph);
	set_number_of_meals(ph);
	ph_sleep(ph->pchrono_ph->time_to_eat);
	ph_msgs(ph, EAT);

	pthread_mutex_unlock(ph->pmutex_right_fork);
	pthread_mutex_unlock(ph->pmutex_left_fork);
}
