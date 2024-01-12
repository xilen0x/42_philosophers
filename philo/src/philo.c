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

void	monitor(t_chrono *chrono)
{
	//fn x check si alguno muere
		//fn x hacer q c/philo coma
		//fn x saber el status de c/philo
		
	//usleep(100);
	//pthread_mutex_lock(&chrono);

	printf("testeeeee\n");
	//printf("%lld %d is eating\n", chrono->start_time, chrono->ph->num_ph);

	//pthread_mutex_unlock(&chrono);
}

int	philos_creation(t_chrono *chrono)
{
	pthread_t		*philosopher;
	unsigned int	i;

	i = 0;
	philosopher = (pthread_t *)malloc(sizeof(pthread_t) * chrono->q_philos);
	if (!philosopher)
		return (1);
	while (i < chrono->q_philos)
	{
		if (pthread_create(&philosopher[i], NULL, (void *)monitor, &chrono->ph[i]))
		{
			printf("Error creating thread\n");
			return (1);
		}
		chrono->ph[i].last_eat = get_time();
		i++;
	}
	return (0);
}
