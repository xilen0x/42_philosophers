/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/01/18 12:37:56 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ph_msgs(t_philo *ph, int n)
{
	if (n == 1)
	{
		usleep(100);
		printf("%lld %u  is eating\n", get_time(ph->chrono_ph), ph->num_ph);
	}
	else if (n == 2)
	{
		usleep(100);
		printf("%lld %u  is sleeping\n", get_time(ph->chrono_ph), ph->num_ph);
	}
	else if (n == 3)
	{
		usleep(100);
		printf("%lld %u  is thinking\n", get_time(ph->chrono_ph), ph->num_ph);
	}
	else if (n == 4)
	{
		usleep(100);
		printf("%lld %u  is die\n", get_time(ph->chrono_ph), ph->num_ph);
	}
	else if (n == 5)
	{
		printf("%lld %u has taken a fork\n", \
			get_time(ph->chrono_ph), ph->num_ph);
	}
}

static void	set_last(t_philo *ph)
{
	pthread_mutex_lock(&ph->chrono_ph->mutex_meal);
	ph->last_eat = get_time(ph->chrono_ph);
	pthread_mutex_unlock(&ph->chrono_ph->mutex_meal);
}

static void	set_iter(t_philo *ph)
{
	pthread_mutex_lock(&ph->chrono_ph->mutex_iter);
	ph->number_of_meals++;
	pthread_mutex_unlock(&ph->chrono_ph->mutex_iter);
}

void	ph_eats(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	ph_msgs(ph, FORK);
	pthread_mutex_lock(ph->right_fork);
	ph_msgs(ph, FORK);
	set_last(ph);
	set_iter(ph);
	ph_msgs(ph, EAT);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	ph_msgs(ph, SLEEP);
}
