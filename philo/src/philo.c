/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/29 16:35:26 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*int	get_its_alive(t_chrono *ch)//main thread access
{
	int	alive;

	//printf("its_alive 1: %d\n", ch->its_alive);
	pthread_mutex_lock(&ch->mutex_its_alive);
	if (ch->its_alive)
		alive = 1;
	else
		alive = 0;
	pthread_mutex_unlock(&ch->mutex_its_alive);
	return (alive);
}*/

int	monitor(t_chrono *ch)//main thread access
{
	int	i;

	i = 0;
	while (ch->its_alive)
	{
		i = 0;
		while (i < ch->q_philos && ch->its_alive)
		{
			pthread_mutex_lock(&ch->pph->mutex_last_eat);
			if (diff_time(ch->pph[i].last_eat, get_time()) >= ch->time_to_die)
			{
				ph_msgs(&ch->pph[i], DIE);
				pthread_mutex_lock(&ch->mutex_its_alive);
				ch->its_alive = 0;
				pthread_mutex_unlock(&ch->mutex_its_alive);
				break ;
			}
			usleep(50);
			pthread_mutex_unlock(&ch->pph->mutex_last_eat);
			i++;
		}
		i = -1;
		while (ch->its_alive && ch->pph[i].number_of_meals == ch->num_x_eat)
		{
			i++;
			if (i == ch->q_philos)
				return (1);
		}
	}
	return (1);
}

void	*philo(t_philo	*ph)//threads section
{
	if (ph->num_ph % 2)
		usleep(1500);
	while (ph->pchrono_ph->its_alive)
	{
		pthread_mutex_lock(&ph->actions);
		ph_eats(ph);
		if ((ph->pchrono_ph->num_x_eat && ph->number_of_meals == \
		ph->pchrono_ph->num_x_eat) || !(ph->pchrono_ph->its_alive))
			break ;
		pthread_mutex_unlock(&ph->actions);
	}
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
			dprintf(2, "Error creating thread\n");
			free(ch->pph);
			return (1);
		}
		ch->pph[i].last_eat = get_time();
		i++;
	}
	//----------contin. thread inicial----*** main thread  access ***
	i = 0;
	monitor(ch);
	while (i < ch->q_philos)
	{
		pthread_join(ch->pph[i].thread, NULL);
		i++;
	}
	return (0);
}
