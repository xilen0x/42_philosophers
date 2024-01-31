/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/31 18:59:17 by castorga         ###   ########.fr       */
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
	while (i < ch->q_philos)
	{
		pthread_mutex_lock(&ch->pph->mutex_last_eat);
		if (diff_time(ch->pph[i].last_eat, get_time(ch)) >= ch->time_to_die)
		{
			ph_msgs(ch->pph, DIE);
			ch->its_alive = 0;
			destroy(ch);//aki voy!!!... falta ver pq sale el error en esta linea
			return (1);
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
		usleep(1500);
	while (get_its_alive(ph->pchrono_ph))
	{
		//pthread_mutex_lock(&ph->mutex_actions);
		ph_eats(ph);
		if ((ph->pchrono_ph->num_x_eat && (ph->number_of_meals == ph->pchrono_ph->num_x_eat)) || !(get_its_alive(ph->pchrono_ph)))
		{
			//pthread_mutex_unlock(&ph->mutex_actions);
			break ;
		}
		ph_msgs(ph, SLEEP);
		ph_sleep_time(ph);
		ph_msgs(ph, THINK);
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
	while (i < ch->q_philos)
	{
		pthread_join(ch->pph[i].thread, NULL);
		i++;
	}
	return (0);
}
