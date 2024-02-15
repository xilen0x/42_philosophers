/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/02/15 16:54:34 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_last_eat(t_philo *ph)
{
	long long	last_eat;

	pthread_mutex_lock(&ph->mutex_last_eat);
	last_eat = ph->last_eat;
	pthread_mutex_unlock(&ph->mutex_last_eat);
	return (last_eat);
}

void	set_last_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_last_eat);
	ph->last_eat = get_current_time(ph->pchrono_ph);
	pthread_mutex_unlock(&ph->mutex_last_eat);
}

int	get_number_of_meals(t_philo *ph)
{
	int	n_o_m;

	pthread_mutex_lock(&ph->mutex_nbr_of_meals);
	n_o_m = ph->number_of_meals;
	pthread_mutex_unlock(&ph->mutex_nbr_of_meals);
	return (n_o_m);
}

void	set_number_of_meals(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex_nbr_of_meals);
	ph->number_of_meals++;
	pthread_mutex_unlock(&ph->mutex_nbr_of_meals);
}

void	ph_eats(t_philo *ph)
{
	pthread_mutex_lock(ph->pmutex_left_fork);
	ph_msgs(ph, "has taken a fork");
	pthread_mutex_lock(ph->pmutex_right_fork);
	ph_msgs(ph, "has taken a fork");
	ph_msgs(ph, "is eating");
	set_number_of_meals(ph);
	set_last_eat(ph);
	ft_usleep(ph->pchrono_ph, ph->pchrono_ph->time_to_eat);
	pthread_mutex_unlock(ph->pmutex_right_fork);
	pthread_mutex_unlock(ph->pmutex_left_fork);
}
