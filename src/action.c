/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/02/08 19:55:41 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*read and return last_eat variable*/
long long	get_last_eat(t_philo *ph)
{
	long long	last_eat;

	pthread_mutex_lock(&ph->mutex_last_eat);
	last_eat = ph->last_eat;
	pthread_mutex_unlock(&ph->mutex_last_eat);
	return (last_eat);
}

/*write last_eat variable*/
void	set_last_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_last_eat);
	ph->last_eat = get_current_time(ph->pchrono_ph);
	pthread_mutex_unlock(&ph->mutex_last_eat);
}

/*increment of number_of_meals variable*/
void	set_number_of_meals(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_nbr_of_meals);
	ph->number_of_meals++;//****
	pthread_mutex_unlock(&ph->mutex_nbr_of_meals);
}

/*eats function(take a fork and more)*/
void	ph_eats(t_philo *ph)
{
	pthread_mutex_lock(ph->pmutex_left_fork);
	ph_msgs(ph, "has taken a fork", 0);
	pthread_mutex_lock(ph->pmutex_right_fork);
	ph_msgs(ph, "has taken a fork", 0);
	ph_msgs(ph, "is eating", 0);
	set_last_eat(ph);
	ft_usleep(ph->pchrono_ph, ph->pchrono_ph->time_to_eat);
	set_number_of_meals(ph);
	pthread_mutex_unlock(ph->pmutex_right_fork);
	pthread_mutex_unlock(ph->pmutex_left_fork);
}
