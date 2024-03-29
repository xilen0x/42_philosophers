/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:54:09 by castorga          #+#    #+#             */
/*   Updated: 2024/02/15 16:54:25 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_chrono	chrono;

	if (parsing(ac, av))
		return (1);
	init_chrono(&chrono, av);
	pthread_mutex_init(&chrono.pph->mutex_msgs, NULL);
	if (chrono.q_philos == 1)
	{
		ph_msgs(chrono.pph, "has taken a fork");
		usleep(chrono.time_to_die * 1000);
		ph_msgs(chrono.pph, "died");
		destroy(&chrono);
		return (0);
	}
	if (philos_creation(&chrono))
		return (destroy(&chrono));
	return (destroy(&chrono));
}
