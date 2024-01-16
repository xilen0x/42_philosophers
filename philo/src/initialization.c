/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:59:15 by castorga          #+#    #+#             */
/*   Updated: 2024/01/16 19:49:49 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*print struct - borrar luego*/
/*void	print_struct(t_chrono *chrono)
{
	printf("start_time: %lld\n", chrono->start_time);
	printf("q_philos: %u\n", chrono->q_philos);
	printf("time_to_die: %zu\n", chrono->time_to_die);
	printf("time_to_eat: %zu\n", chrono->time_to_eat);
	printf("time_to_sleep: %zu\n", chrono->time_to_sleep);
	printf("num_x_eat: %zu\n", chrono->num_x_eat);
}*/

/*Initialization of the philosophers structure(t_philo)*/
static int	init_ph(t_chrono *chrono)//aki voy!!!!!!!!!!!... creo q esta funcion ya esta....creo
{
	unsigned int	i;

	i = 0;
	chrono->ph = NULL;
	chrono->forks = NULL;
	chrono->ph = (t_philo *)malloc(sizeof(t_philo) * chrono->q_philos);
	chrono->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * chrono->q_philos);
	if (!chrono->ph || !chrono->forks)
		ft_free(chrono);
	while (i < chrono->q_philos)
		pthread_mutex_init(&chrono->forks[i], NULL);
	i = 0;
	while (i < chrono->q_philos)
	{
		chrono->ph[i].chrono_ph = chrono;
		chrono->ph[i].num_ph = i + 1;
		chrono->ph[i].last_eat = 0;
		chrono->ph[i].left_fork = &chrono->forks[i];
		if (i == chrono->q_philos)
			chrono->ph[i].right_fork = &chrono->forks[0];
		else
			chrono->ph[i].right_fork = &chrono->forks[i + 1];
		chrono->ph[i].number_of_meals = 0;
		i++;
	}
	return (0);
}

/*Initialization of the chronogram structure(t_chrono)*/
void	init_chrono(t_chrono *chrono, char *av[])
{
	if (pthread_mutex_init(&chrono->mutex_meal, NULL))
	{
		fprintf(stderr, "Error initializing mutex\n");
		return ;
	}
	if (pthread_mutex_init(&chrono->mutex_iter, NULL))
	{
		fprintf(stderr, "Error initializing mutex\n");
		return ;
	}
	chrono->q_philos = ft_atol(av[1]);
	chrono->time_to_die = ft_atol(av[2]);
	chrono->time_to_eat = ft_atol(av[3]);
	chrono->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		chrono->num_x_eat = ft_atol(av[5]);
	else
		chrono->num_x_eat = 0;
	chrono->are_all_alive = 1;
	chrono->start_time = get_time(chrono);
	//print_struct(chrono);
	init_ph(chrono);
}
