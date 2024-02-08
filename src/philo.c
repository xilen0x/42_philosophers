/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/02/08 19:55:26 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Messages fuction*/
void ph_msgs(t_philo *ph, char *msg, int monitor)
{
	//if (ph->pchrono_ph->its_alive)
	if (get_its_alive(ph->pchrono_ph))
	{
		pthread_mutex_lock(&ph->pchrono_ph->mutex_msgs);
		printf("%lld %u %s\n", get_current_time(ph->pchrono_ph), \
			ph->num_ph, msg);
		pthread_mutex_unlock(&ph->pchrono_ph->mutex_msgs);
		return ;
	}
	else if (monitor)
	{
		printf("%lld %u %s\n", get_current_time(ph->pchrono_ph), \
			ph->num_ph, msg);
	}
}

/*int	all_ate(t_philo	*ph)
{
	pthread_mutex_lock(&ph->mutex_nbr_of_meals);
	if (ph->pchrono_ph->num_x_eat == ph->number_of_meals)
	{
		pthread_mutex_unlock(&ph->mutex_nbr_of_meals);
		return (0);
	}
	pthread_mutex_unlock(&ph->mutex_nbr_of_meals);
	return (1);
}*/

/*monitor function, checking TTD of each thread*/
int	monitor(t_chrono *ch)
{
	int			i;
	long long	res;

	i = 0;
	while (i < ch->q_philos)
	{
		pthread_mutex_lock(&ch->pph[i].mutex_last_eat);
		res = (get_current_time(ch) - ch->pph[i].last_eat);
		pthread_mutex_unlock(&ch->pph[i].mutex_last_eat);
		if (res >= ch->time_to_die)
		{
			set_its_alive(ch);
			ph_msgs(&ch->pph[i], "died", 1);
			return (0);
		}
		if (ch->opt && (ch->num_x_eat == ch->pph[i].number_of_meals))
		{	
			set_its_alive(ch);
			ph_msgs(&ch->pph[i], "all philos have eaten enough!", 1);
			break ;
		}
		i++;
		if (i == ch->q_philos)
			i = 0;
	}
	return (0);
}

/*threads section - EATS, SLEEP, THINK*/
void	*philo(t_philo	*ph)
{
	if (ph->num_ph % 2)
		ft_usleep(ph->pchrono_ph, ph->pchrono_ph->time_to_eat * 0.9);
	while (get_its_alive(ph->pchrono_ph))
	{
		ph_eats(ph);
		(ph_msgs(ph, "is sleeping", 0));
		ft_usleep(ph->pchrono_ph, ph->pchrono_ph->time_to_sleep);
		ph_msgs(ph, "is thinking", 0);
	}
	return (NULL);
}

/*Function where the threads area created*/
int	philos_creation(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		if (pthread_create(&ch->pph[i].thread, NULL, \
			(void *)philo, &ch->pph[i]))
		{
			printf("Error creating thread\n");
			destroy(ch);
			return (1);
		}
		// pthread_mutex_lock(&ch->mutex_last_eat);
		// ch->pph[i].last_eat = get_current_time(ch);
		// pthread_mutex_unlock(&ch->mutex_last_eat);
		i++;
	}
	monitor(ch);
	i = 0;
	while (i < ch->q_philos)
	{
		if (pthread_join(ch->pph[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}
