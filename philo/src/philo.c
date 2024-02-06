/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/02/06 15:32:24 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	get_its_alive(t_chrono *ch)//common access function
{
	int	alive;

	pthread_mutex_lock(&ch->mutex_its_alive);
	if (ch->its_alive)
		alive = 1;
	else
		alive = 0;
		//ch->its_alive = 0;
	pthread_mutex_unlock(&ch->mutex_its_alive);
	return (alive);
}*/

int monitor(t_chrono *ch)
{
    int i;

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
		if (((ph->number_of_meals == ph->pchrono_ph->num_x_eat)) || !(ph->pchrono_ph->its_alive))
			break ;
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
			//free(ch->pph);
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
