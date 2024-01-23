/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/23 18:47:41 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_its_alive(t_chrono *ch)
{
	pthread_mutex_lock(&ch->mutex_its_alive);
	return (ch->its_alive);
	pthread_mutex_unlock(&ch->mutex_its_alive);
}

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

static void	*philo(t_philo *ph)
{
	//printf("its_alive: %d\n", phi->chrono_ph->its_alive);
	if (ph->num_ph % 2)
		usleep(100);
	while (get_its_alive(ph->chrono_ph))
	{
		printf("llega aqui?\n");
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
	int			i;

	i = 0;
	while (i < ch->q_philos)
	{
		if (pthread_create(&ch->ph[i].thread, NULL, (void *(*)(void *))philo, &ch->ph[i]))
		{
			printf("Error creating thread\n");
			free(ch->ph);
			return (1);
		}
		i++;
	}
	//----------hilo inicial----------
	i = 0;
	did_anyone_die(ch);
	while (i < ch->q_philos)
	{
		pthread_join(ch->ph[i].thread, NULL);
		i++;
	}
	return (0);
}
