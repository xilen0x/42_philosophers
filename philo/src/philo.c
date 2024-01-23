/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/23 12:08:49 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_its_alive(t_chrono *ch)
{
	pthread_mutex_lock(&ch->mutex_its_alive);
	return (ch->its_alive);
	pthread_mutex_unlock(&ch->mutex_its_alive);
}

/*por aqui voy...
*he creado la funcion getter get_its_alive
*falta corregir el tiempo, 1 ph debe morir en 800 y esta muriendo en 0
*/

int	did_anyone_die(t_chrono *ch)
{
	size_t	i;

	i = 0;
	while (get_its_alive(ch))
	{
		pthread_mutex_lock(&ch->ph->mutex_last_eat);
		if ((get_time() - ch->ph[i].last_eat) > ch->time_to_die)
		{
			ch->its_alive = 0;
			ph_msgs(&ch->ph[i], DIE);
		}
		pthread_mutex_unlock(&ch->ph->mutex_last_eat);
		if (ch->its_alive == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	*philo(void *ph)
{
	t_philo *phi;

	phi = (t_philo *)ph;
	printf("its_alive: %d\n", phi->chrono_ph->its_alive);
	if (phi->num_ph % 2)
		usleep(100);
	while (get_its_alive(phi->chrono_ph))
	{
		printf("llega aqui?\n");
		ph_eats(phi);
		ph_sleep(phi->chrono_ph->time_to_sleep);
		ph_msgs(phi, SLEEP);
		ph_msgs(phi, THINK);
	}
	return (NULL);
}

//Function to create the threads
int	philos_creation(t_chrono *ch)
{
	pthread_t	*thread_ids;
	int			i;

	i = 0;
	thread_ids = (pthread_t *)malloc(sizeof(pthread_t) * ch->q_philos);
	if (!thread_ids)
		return (1);
	while (i < ch->q_philos)
	{
		if (pthread_create(&thread_ids[i], NULL, (void *(*)(void *))philo, &ch->ph[i]))
		{
			printf("Error creating thread\n");
			free(thread_ids);
			return (1);
		}
		i++;
	}
	//----------hilo inicial----------
	i = 0;
	did_anyone_die(ch);
	while (i < ch->q_philos)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
	return (0);
}
