/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/01/19 13:28:05 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ph_msgs(t_philo *ph, int n)
{
	pthread_mutex_lock(&ph->mutex_msgs);
	if (n == FORK)
	{
		printf("%lld %u has taken a fork\n", difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	}
	else if (n == EAT)
	{
		printf("%lld %u is eating\n", difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	}
	else if (n == SLEEP)
	{
		printf("%lld %u is sleeping\n", difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	}
	else if (n == THINK)
	{
		printf("%lld %u is thinking\n", difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	}
	else if (n == DIE)
	{
		printf("%lld %u died\n", difference_of_time(ph->chrono_ph->start_time, get_time()), ph->num_ph);
	}
	pthread_mutex_unlock(&ph->mutex_msgs);
}

void	ph_sleep(long long time)
{
	long long	cu_time;

	cu_time = get_time();
	while (1)
	{
		if (difference_of_time(cu_time, get_time()) >= time)
		{
			break ;
		}
		usleep(150);
	}
}

static void	set_last_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->chrono_ph->mutex_last_eat);
	ph->last_eat = get_time();
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
	int	i;

	i = 0;
	pthread_mutex_lock(ph[i].left_fork);
	ph_msgs(ph, FORK);
	pthread_mutex_lock(ph[i].right_fork);
	ph_msgs(ph, FORK);
	ph_msgs(ph, EAT);
	set_last_eat(ph);
	ph_sleep(ph->chrono_ph->time_to_eat);
	set_number_of_meals(ph);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}
