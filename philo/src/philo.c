/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/18 13:11:16 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	did_anyone_die(t_philo *ph)
{
	size_t	i;

	i = 0;
	while ((ph->chrono_ph->its_alive) && i < ph->chrono_ph->q_philos)
	{
		pthread_mutex_lock(&ph->chrono_ph->mutex_meal);
		if ((ph->last_eat - get_time(ph->chrono_ph)) < ph->chrono_ph->time_to_die)
		{
			ph_msgs(ph, DIE);
			ph->chrono_ph->its_alive = 0;
		}
		pthread_mutex_unlock(&ph->chrono_ph->mutex_meal);
		if (!(ph->chrono_ph->its_alive))
			break ;
	}
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
	//-----------de aqui en adelante, continúa el hilo principal----------
	i = 0;
	did_anyone_die(ch->ph);//funcion monitor
	while (i < ch->q_philos)
	{
		pthread_join(thread_ids[i], NULL);
		i++;
	}
	return (0);
}
