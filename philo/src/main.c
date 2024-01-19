/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:54:09 by castorga          #+#    #+#             */
/*   Updated: 2024/01/19 14:37:07 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Turn in files 
Makefile, *.h, *.c, in directory philo/

Makefile 
NAME, all, clean, fclean, re

Arguments 
number_of_philosophers time_to_die time_to_eat time_to_sleep[number_of_times_each_philosopher_must_eat]

External functs. 
memset, printf, malloc, free, write, usleep, gettimeofday, 
pthread_create, pthread_detach, pthread_join, 
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

The specific rules for the mandatory part are:
• Each philosopher should be a thread.
• There is one fork between each pair of philosophers. Therefore, if there are several
	philosophers, each philosopher has a fork on their left side and a fork on their right
	side. If there is only one philosopher, there should be only one fork on the table.
• To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.
https://www.figma.com/file/KG3b82Ss33nnkI1j3b5y4r/Untitled?type=whiteboard&node-id=11%3A8&t=cCpQ6EutW4RmbLa4-1
*/

#include "../include/philo.h"

int	main(int ac, char *av[])
{
	t_chrono	chrono;

	//parsing arguments
	if (parsing(ac, av))
		return (1);

	//initializing structs (chrono y ph)
	init_chrono(&chrono, av);

	//threads creation
	if (philos_creation(&chrono))
	{
		//llamar a fnc x liberar recursos
	}

	//release resources
	pthread_mutex_destroy(&chrono.mutex_last_eat);
	pthread_mutex_destroy(&chrono.ph->mutex_msgs);
	//pthread_mutex_destroy(&chrono.mutex_nbr_of_meals);
	//printf("testX\n");
	free(chrono.ph);
	return (0);
}
