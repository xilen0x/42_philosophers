/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/02/01 11:45:57 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ph_msgs(t_philo *ph, int n)//threads access
{
	if (n == FORK)
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u has taken a fork\n", \
		diff_time(ph->pchrono_ph->start_time, get_time(ph->pchrono_ph)), ph->num_ph);
		pthread_mutex_unlock(&ph->mutex_msgs);
	}
	else if (n == EAT)
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u is eating\n", \
		diff_time(ph->pchrono_ph->start_time, get_time(ph->pchrono_ph)), ph->num_ph);
		pthread_mutex_unlock(&ph->mutex_msgs);
	}
	else if (n == SLEEP)
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u is sleeping\n", \
		diff_time(ph->pchrono_ph->start_time, get_time(ph->pchrono_ph)), ph->num_ph);
		pthread_mutex_unlock(&ph->mutex_msgs);
	}
	else if (n == THINK)
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u is thinking\n", \
		diff_time(ph->pchrono_ph->start_time, get_time(ph->pchrono_ph)), ph->num_ph);
		pthread_mutex_unlock(&ph->mutex_msgs);
	}
	else if (n == DIE)
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u died\n", \
		diff_time(ph->pchrono_ph->start_time, get_time(ph->pchrono_ph)), ph->num_ph);
		pthread_mutex_unlock(&ph->mutex_msgs);
	}
}

/*int	ph_to_die_time(t_philo *ph)//threads access
{
	long long	cu_time;
	long long	ttd;
	int			i;

	i = 0;
	pthread_mutex_lock(&ph->pchrono_ph->mutex_its_alive);
	ttd = ph->pchrono_ph->time_to_die;
	cu_time = get_time();
	while (get_its_alive(ph->pchrono_ph))
	{
		if (diff_time(ph[i].last_eat, get_time()) >= ttd)
		{
			//ph_msgs(ph, DIE);
			ph->pchrono_ph->its_alive = 0;
			pthread_mutex_unlock(&ph->pchrono_ph->mutex_its_alive);
			return (1);
		}
		pthread_mutex_unlock(&ph->pchrono_ph->mutex_its_alive);
		usleep(1000);
		i++;
	}
	return (0);
}*/

void	ph_sleep_time(t_philo *ph)//threads access
{
	long long	cu_time;
	long long	tts;

	pthread_mutex_lock(&ph->pchrono_ph->mutex_times);
	tts = ph->pchrono_ph->time_to_sleep;
	cu_time = get_time(ph->pchrono_ph);
	while (1)
	{
		if (diff_time(cu_time, get_time(ph->pchrono_ph)) >= tts)
			break ;
		//usleep(1000);
	}
	pthread_mutex_unlock(&ph->pchrono_ph->mutex_times);
}

void	ph_eats_time(t_philo *ph)//threads access
{
	long long	cu_time;
	long long	tte;

	pthread_mutex_lock(&ph->pchrono_ph->mutex_times);
	tte = ph->pchrono_ph->time_to_eat;
	cu_time = get_time(ph->pchrono_ph);
	while (1)
	{
		if (diff_time(cu_time, get_time(ph->pchrono_ph)) >= tte)
			break ;
		//usleep(1000);
	}
	pthread_mutex_unlock(&ph->pchrono_ph->mutex_times);
}

void	set_last_eat(t_philo *ph)//threads access
{
	pthread_mutex_lock(&ph->mutex_last_eat);
	ph->last_eat = get_time(ph->pchrono_ph);
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
	pthread_mutex_lock(&ph->mutex_actions);
	ph_msgs(ph, EAT);
	ph_eats_time(ph);
	set_last_eat(ph);
	set_number_of_meals(ph);
	pthread_mutex_unlock(&ph->mutex_actions);
	pthread_mutex_unlock(ph->pmutex_right_fork);
	pthread_mutex_unlock(ph->pmutex_left_fork);
}
