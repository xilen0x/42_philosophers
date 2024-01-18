/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/18 15:04:13 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	did_anyone_die(t_chrono *ch)
{
	size_t	i;

	i = 0;
	while ((ch->its_alive))
	{
		pthread_mutex_lock(&ch->mutex_last_eat);
		if ((ch->ph->last_eat - get_time(ch)) < ch->time_to_die)
		{
			ph_msgs(ch->ph, DIE);
			ch->its_alive = 0;
		}
		pthread_mutex_unlock(&ch->mutex_last_eat);
		if (ch->its_alive == 0)
			return (1);
	}
	return (0);
}

static void	*th_fnctn(t_philo *ph)
{
	if (ph->num_ph % 2)
		usleep(100);
	while (ph->chrono_ph->its_alive)
	{
		ph_eats(ph);
		ph_msgs(ph, SLEEP);
		ph_msgs(ph, THINK);
	}
	return (NULL);
}

//Function to create the threads
int	philos_creation(t_chrono *ch)
{
	pthread_t		*thread_ids;
	unsigned int	i;

	i = 0;
	thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * ch->q_philos);
	if (!thread_ids)
		return (1);
	while (i < ch->q_philos)
	{
		if (pthread_create(&thread_ids[i], NULL, (void *)th_fnctn, &ch->ph[i]))
		{
			printf("Error creating thread\n");
			return (1);
		}
		i++;
	}
	//-----------de aqui en adelante, continúa el hilo inicial----------
	i = 0;
	did_anyone_die(ch);
	while (i < ch->q_philos)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
	return (0);
}
