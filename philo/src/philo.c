/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/19 14:56:35 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	did_anyone_die(t_chrono *ch)
{
	size_t	i;

	i = 0;
	while ((ch->its_alive))
	{
		pthread_mutex_lock(&ch->ph[i].chrono_ph->mutex_last_eat);
		if ((ch->ph[i].last_eat - get_time()) < ch->time_to_die)
		{
			ph_msgs(&ch->ph[i], DIE);
			ch->its_alive = 0;
		}
		pthread_mutex_unlock(&ch->ph[i].chrono_ph->mutex_last_eat);
		if (ch->its_alive == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	*th_fnctn(t_philo *ph)
{
	if (ph->num_ph % 2)
		usleep(1000);
	while (ph->chrono_ph->its_alive)
	{
		ph_eats(ph);
		ph_sleep(ph->chrono_ph->time_to_sleep);
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
			free(thread_ids);
			return (1);
		}
		i++;
	}
	//----------hilo inicial----------
	i = 0;
	if (did_anyone_die(ch) == 1)
	{
		//llamar a fnc x liberar recursos
		free(thread_ids);
		return (0);
	}
	while (i < ch->q_philos)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
	return (0);
}
