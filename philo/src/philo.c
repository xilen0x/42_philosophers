/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/02/01 18:32:33 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_its_alive(t_chrono *ch)//common access function
{
	int	alive;

	pthread_mutex_lock(&ch->mutex_its_alive);
	if (ch->its_alive)
		alive = 1;
	else
		alive = 0;
		//ch->its_alive = 0;
	pthread_mutex_unlock(&ch->mutex_its_alive);
	return (alive);
}

int	monitor(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		pthread_mutex_lock(&ch->pph->mutex_last_eat);
		if (diff_time(ch->pph[i].last_eat, get_time(ch)) >= ch->time_to_die)
		{
			ph_msgs(ch->pph, "died");
			usleep(1000);
			ch->its_alive = 0;
			//printf("teste\n");
			destroy(ch);
			pthread_mutex_unlock(&ch->pph->mutex_last_eat);
			return (0);
		}
		i++;
		if (i == ch->q_philos)
			i = 0;
		pthread_mutex_unlock(&ch->pph->mutex_last_eat);
	}
	return (0);
}

void	*philo(t_philo	*ph)//threads section
{
	if (ph->num_ph % 2)
		usleep(1000);
	//while (get_its_alive(ph->pchrono_ph))
	while (ph->pchrono_ph->its_alive)
	{
		//pthread_mutex_lock(&ph->mutex_actions);
		ph_eats(ph);
		if (((ph->number_of_meals == ph->pchrono_ph->num_x_eat)) || !(get_its_alive(ph->pchrono_ph)))
		{
			//pthread_mutex_unlock(&ph->mutex_actions);
			break ;
		}
		ph_msgs(ph, "is sleeping");
		ph_sleep_time(ph);
		ph_msgs(ph, "is thinking");
	}
	//pthread_mutex_unlock(&ph->mutex_actions);
	return (NULL);
}

//Function to create the threads
int	philos_creation(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		if (pthread_create(&ch->pph[i].thread, NULL, (void *)philo, &ch->pph[i]))
		{
			printf("Error creating thread\n");
			free(ch->pph);
			return (1);
		}
		ch->pph[i].last_eat = get_time(ch);
		i++;
	}
	//----------contin. thread inicial----*** main thread  access ***
	i = 0;
	monitor(ch);
	// while (i < ch->q_philos)
	// {
	// 	pthread_join(ch->pph[i].thread, NULL);
	// 	i++;
	// }
	return (0);
}
