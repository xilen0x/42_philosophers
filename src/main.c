/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:54:09 by castorga          #+#    #+#             */
/*   Updated: 2024/02/08 19:56:01 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_chrono	chrono;

	if (parsing(ac, av))
		return (1);
	init_chrono(&chrono, av);
	pthread_mutex_init(&chrono.mutex_msgs, NULL);
	if (chrono.q_philos == 1)
	{
		ph_msgs(&chrono.pph[0], "has taken a fork", 1);
		usleep(chrono.time_to_die * 1000);
		ph_msgs(&chrono.pph[0], "died", 1);
		destroy(&chrono);
		return (0);
	}
	if (philos_creation(&chrono))
		return (destroy(&chrono));
	return (destroy(&chrono));
}
