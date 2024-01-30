/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/30 18:24:57 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_its_alive(t_chrono *ch)//main thread access
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

int	monitor(t_chrono *ch)
{
	int	i;

	i = 0;
	while (get_its_alive(ch))
	{
		pthread_mutex_lock(&ch->pph->mutex_last_eat);
		if (diff_time(ch->pph[i].last_eat, get_time()) >= ch->time_to_die)
		{
			ch->its_alive = 0;
			pthread_mutex_unlock(&ch->pph->mutex_last_eat);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&ch->pph->mutex_last_eat);
	return (0);
}

/*int	monitor(t_chrono *ch)//main thread access
{
	int	i;

	i = 0;
	pthread_mutex_lock(&ch->mutex_its_alive);
	while (i < ch->q_philos && ch->its_alive)
	{
		pthread_mutex_lock(&ch->pph->mutex_last_eat);
		if (diff_time(ch->pph[i].last_eat, get_time()) >= ch->time_to_die)
		{
			printf("test\n");
			ph_msgs(&ch->pph[i], DIE);
			ch->its_alive = 0;
			pthread_mutex_unlock(&ch->mutex_its_alive);
			break ;
		}
		usleep(50);
		pthread_mutex_unlock(&ch->pph->mutex_last_eat);
		i++;
	}
	pthread_mutex_unlock(&ch->mutex_its_alive);
	//printf("i: %d\n", i);
	i = 0;
	while (ch->its_alive && ch->pph[i].number_of_meals == ch->num_x_eat)
	{
		i++;
		pthread_mutex_unlock(&ch->mutex_its_alive);
		if (i == ch->q_philos)
			return (0);
	}
	pthread_mutex_unlock(&ch->mutex_its_alive);
	return (1);
}*/

void	*philo(t_philo	*ph)//threads section
{
	if (ph->num_ph % 2)
		usleep(1500);
	//while (get_its_alive(ph->pchrono_ph))
	while (ph->pchrono_ph->its_alive)
	{
		pthread_mutex_lock(&ph->mutex_actions);
		ph_eats(ph);
		if ((ph->number_of_meals == ph->pchrono_ph->num_x_eat) || (ph->pchrono_ph->its_alive == 0))
		{
			pthread_mutex_unlock(&ph->mutex_actions);
			break ;
		}
	}
	pthread_mutex_unlock(&ph->mutex_actions);
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
		//ch->pph[i].last_eat = get_time();
		i++;
	}
	//----------contin. thread inicial----*** main thread  access ***
	i = 0;
	//monitor(ch);
	while (i < ch->q_philos)
	{
		pthread_join(ch->pph[i].thread, NULL);
		i++;
	}
	return (0);
}
