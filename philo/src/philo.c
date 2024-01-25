/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/25 18:27:27 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_its_alive(t_chrono *ch)//main thread access
{
	int	alive;

	pthread_mutex_lock(&ch->mutex_its_alive);
	//printf("teste\n");
	if (ch->its_alive)
		alive = 1;
	else
		alive = 0;
	pthread_mutex_unlock(&ch->mutex_its_alive);
	return (alive);
}

int	did_anyone_die(t_chrono *ch)//main thread access
{
	size_t	i;

	i = 0;
	while (get_its_alive(ch))
	{
		i = 0;
		pthread_mutex_lock(&ch->pph->mutex_last_eat);
		if ((get_time() - ch->start_time - ch->pph[i].last_eat) > ch->time_to_die)
		{
	dprintf(2, "testxxxxxxxx\n");
			ch->its_alive = 0;
			ph_msgs(&ch->pph[i], DIE);
		}
		pthread_mutex_unlock(&ch->pph->mutex_last_eat);
		if (ch->its_alive == 0)
			return (0);
		i++;
	}
	return (1);
}

void	*philo(void *arg)//threads section
{
	t_philo	*ph;
	int		i;

	ph = (t_philo *)arg;
	i = 0;
	if (ph->pchrono_ph->q_philos == 1)
	{
		pthread_mutex_lock(ph->pmutex_left_fork);
		ph_msgs(ph, FORK);
		pthread_mutex_unlock(ph->pmutex_left_fork);
	}
	else
	{
		if (ph->num_ph % 2)
			usleep(100);
		while (i < ph->pchrono_ph->q_philos)
		{
			ph_eats(ph);
			ph_sleep(ph->pchrono_ph->time_to_sleep);
			ph_msgs(ph, SLEEP);
			ph_msgs(ph, THINK);
			i++;
		}
	}
	return (NULL);
}

//Function to create the threads
int	philos_creation(t_chrono *ch)
{
	int			i;

	i = 0;
	while (i < (ch->q_philos))
	{
		if (pthread_create(&ch->pph[i].thread, NULL, philo, (void *)&ch->pph[i]))
		{
			dprintf(2, "Error creating thread\n");
			free(ch->pph);
			return (1);
		}
		i++;
	}
	//----------contin. thread inicial----*** main thread  access ***
	i = 0;
	did_anyone_die(ch);
	while (i < ch->q_philos)
	{
		pthread_join(ch->pph[i].thread, NULL);
		i++;
	}
	return (0);
}
