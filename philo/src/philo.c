/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/02/14 17:29:14 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		if ((get_current_time(ch) - get_last_eat(ch->pph)) >= ch->time_to_die)
		{
			ph_msgs(ch->pph, "died");
			set_its_alive(ch);
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
	while (get_its_alive(ph->pchrono_ph))
	{
		ph_eats(ph);
		if ((ph->pchrono_ph->num_x_eat && ph->number_of_meals == ph->pchrono_ph->num_x_eat) )
		{
			printf("Philo %d ha completado el N de comidas!\n", ph->num_ph);
			//set_its_alive(ph->pchrono_ph);//aqui esta casi bien...ver pq sale el 'die'
			break ;
		}
		ph_msgs(ph, "is sleeping");
		ft_usleep(ph->pchrono_ph, ph->pchrono_ph->time_to_sleep);
		ph_msgs(ph, "is thinking");
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
