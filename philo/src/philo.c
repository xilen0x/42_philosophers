/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/04 16:33:52 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	functionx(t_chrono *chrono)
{
	(void)chrono;
	pthread_mutex_lock(&mutex);
//aki voy!!!!!!!!
	pthread_mutex_unlock(&mutex);
}

int	philos_creation(t_chrono *chrono)
{
	pthread_t		*ph_ptr;
	unsigned int	i;

	i = 0;
	ph_ptr = (pthread_t *)malloc(sizeof(pthread_t) * chrono->q_philos);
	if (!ph_ptr)
		return (1);
	while (i < chrono->q_philos)
	{
		pthread_create(&ph_ptr[i], NULL, (void *(*)(void *))functionx, &chrono->ph[i]);
		chrono->ph[i].last_eat = get_time();
		i++;
	}
	return (0);
}
