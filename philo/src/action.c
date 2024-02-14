/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:37:53 by castorga          #+#    #+#             */
/*   Updated: 2024/02/14 14:15:38 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

int	get_its_alive(t_chrono *ch)//common access function
{
	int	alive;

	pthread_mutex_lock(&ch->mutex_its_alive);
	if (ch->its_alive)
		alive = 1;
	else
		alive = 0;
	pthread_mutex_unlock(&ch->mutex_its_alive);
	return (alive);
}

void	ph_msgs(t_philo *ph, char *msg)//common access f
{
	//if (ph->pchrono_ph->its_alive)
	if (get_its_alive(ph->pchrono_ph))
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u %s\n", get_current_time(ph->pchrono_ph), ph->num_ph, msg);
		pthread_mutex_unlock(&ph->mutex_msgs);
		return ;
	}
}

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
	set_last_eat(ph);
	set_number_of_meals(ph);
	ft_usleep(ph->pchrono_ph, ph->pchrono_ph->time_to_eat);

	pthread_mutex_unlock(ph->pmutex_right_fork);
	pthread_mutex_unlock(ph->pmutex_left_fork);

}
