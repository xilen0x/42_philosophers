/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/01/18 14:47:00 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ph_msgs(t_philo *ph, int n)
{
	if (n == EAT)
	{
		usleep(1000);
		printf("%lld %u is eating\n", get_time(ph->chrono_ph), ph->num_ph);
	}
	else if (n == SLEEP)
	{
		usleep(1000);
		printf("%lld %u is sleeping\n", get_time(ph->chrono_ph), ph->num_ph);
	}
	else if (n == THINK)
	{
		usleep(1000);
		printf("%lld %u is thinking\n", get_time(ph->chrono_ph), ph->num_ph);
	}
	else if (n == DIE)
	{
		usleep(1000);
		printf("%lld %u died\n", get_time(ph->chrono_ph), ph->num_ph);
	}
	else if (n == FORK)
	{
		printf("%lld %u has taken a fork\n", \
			get_time(ph->chrono_ph), ph->num_ph);
	}
}

static void	set_last_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->chrono_ph->mutex_last_eat);
	ph->last_eat = get_time(ph->chrono_ph);
	pthread_mutex_unlock(&ph->chrono_ph->mutex_last_eat);
}

static void	set_number_of_meals(t_philo *ph)
{
	pthread_mutex_lock(&ph->chrono_ph->mutex_nbr_of_meals);
	ph->number_of_meals++;
	pthread_mutex_unlock(&ph->chrono_ph->mutex_nbr_of_meals);
}

void	ph_eats(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	ph_msgs(ph, FORK);
	pthread_mutex_lock(ph->right_fork);
	ph_msgs(ph, FORK);
	set_last_eat(ph);
	set_number_of_meals(ph);
	ph_msgs(ph, EAT);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	ph_msgs(ph, SLEEP);
}
