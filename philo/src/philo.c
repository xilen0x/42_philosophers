/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/24 18:40:35 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_its_alive(t_chrono *ch)
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

int	did_anyone_die(t_chrono *ch)
{
	size_t	i;

	i = 0;
	while (get_its_alive(ch))
	{
		pthread_mutex_lock(&ch->mutex_its_alive);
		if ((get_time() - ch->start_time - ch->pph[i].last_eat) > ch->time_to_die)
		{
			ch->its_alive = 0;
			ph_msgs(&ch->pph[i], DIE);
		}
		pthread_mutex_unlock(&ch->mutex_its_alive);
		if (ch->its_alive == 0)
			return (0);
		//i++;
	}
	return (1);
}

static void	*philo(t_philo *ph)
{
	printf("its_alive: %d\n", ph->pchrono_ph->its_alive);
	// if (ph->num_ph > 1 && ph->num_ph % 2)
		// usleep(100);
	while (get_its_alive(ph->pchrono_ph))
	{
		printf("llega aqui?\n");
		ph_eats(ph);
		ph_sleep(ph->pchrono_ph->time_to_sleep);
		ph_msgs(ph, SLEEP);
		ph_msgs(ph, THINK);
	}
	printf("its_alive: %d\n", ph->pchrono_ph->its_alive);
	return (NULL);
}

//Function to create the threads
int	philos_creation(t_chrono *ch)
{
	int			i;

	i = 0;
	while (i < ch->q_philos)
	{
		if (pthread_create(&ch->pph[i].thread, NULL, (void *(*)(void *))philo, &ch->pph[i]))
		{
			printf("Error creating thread\n");
			free(ch->pph);
			return (1);
		}
		//set_last_eat(ch->pph);
		//ph_msgs(ch->pph, SLEEP);
		//ph_msgs(ch->pph, THINK);
		i++;
	}
	//----------hilo inicial----------
	i = 0;
	did_anyone_die(ch);
	while (i < ch->q_philos)
	{
		pthread_join(ch->pph[i].thread, NULL);
		i++;
	}
	return (0);
}
