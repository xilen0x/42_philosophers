/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/02/07 13:41:10 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_msgs(t_philo *ph, char *msg)//common access f
{
	if (get_its_alive(ph->pchrono_ph))
	{
		pthread_mutex_lock(&ph->mutex_msgs);
		printf("%lld %u %s\n", get_current_time(ph->pchrono_ph), ph->num_ph, msg);
		pthread_mutex_unlock(&ph->mutex_msgs);
		return ;
	}
}

int	monitor(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		if ((get_current_time(ch) - ch->pph->last_eat) >= ch->time_to_die)
		{
			ph_msgs(ch->pph, "died");
			ch->its_alive = 0;
			return (0);
		}
		i++;
		if (i == ch->q_philos)
			i = 0;
	}
	return (0);
}

//threads section - EATS, SLEEP, THINK
void	*philo(t_philo	*ph)
{
	if (ph->num_ph % 2)
		ft_usleep(ph->pchrono_ph, ph->pchrono_ph->time_to_eat * 0.9);
	while (ph->pchrono_ph->its_alive)
	{
		ph_eats(ph);
		ph_msgs(ph, "is sleeping");
		ft_usleep(ph->pchrono_ph, ph->pchrono_ph->time_to_sleep);
		ph_msgs(ph, "is thinking");
		if (ph->number_of_meals == ph->pchrono_ph->num_x_eat)
		{
			//printf("Philo %d ha completado el N de comidas!\n", ph->num_ph);
			ph->pchrono_ph->its_alive = 0;
			break ;
		}
	}
	return (NULL);
}

//Function where the threads area created
int	philos_creation(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		if (pthread_create(&ch->pph[i].thread, NULL, (void *)philo, &ch->pph[i]))
		{
			printf("Error creating thread\n");
			destroy(ch);
			return (1);
		}
		ch->pph[i].last_eat = get_current_time(ch);
		i++;
	}
	monitor(ch);
	i = 0;
	while (i < ch->q_philos)
	{
		if (pthread_join(ch->pph[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
}
