/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:59:15 by castorga          #+#    #+#             */
/*   Updated: 2024/01/04 18:59:17 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
/* 
number_of_philosophers 		time_to_die 		time_to_eat 		time_to_sleep[number_of_times_each_philosopher_must_eat]
		1 200 250 100 5   */

/*print struct - borrar luego*/
void	print_struct(t_chrono *chrono)
{
	printf("num_ph: %u\n", chrono->ph->num_ph);
	printf("time_to_die: %zu\n", chrono->time_to_die);
	printf("time_to_eat: %zu\n", chrono->time_to_eat);
	printf("time_to_sleep: %zu\n", chrono->time_to_sleep);
	printf("num_x_ph_must_eat: %zu\n", chrono->num_x_ph_must_eat);
	printf("num_x_ph_must_eat: %lld\n", chrono->start_time);
}

/*Inicializacion de philosofos(threads)*/
void	init_ph(t_chrono *chrono)
{
	unsigned int	i;

	i = 0;
	chrono->ph = NULL;
	chrono->ph = malloc(sizeof(t_philo) * chrono->ph->num_ph);
	if (!chrono)
	{
		printf("Error reserving memory!\n");
		free(chrono);
		return ;
	}
	while (i < chrono->ph->num_ph)
	{
		pthread_mutex_init(&chrono->ph[i].fork, NULL);
		chrono->ph[i].chrono_ph = chrono;
		chrono->ph[i].num_ph = i + 1;
		chrono->ph[i].last_eat = 0;
		chrono->ph[i].rigth_fork = i + 1;
		chrono->ph[i].left_fork = i;
		i++;
	}
}

/*Inicializacion de la estructura t_chrono*/
void	init_chrono(t_chrono *chrono, char *av[])
{
	pthread_mutex_init(&chrono->writing, NULL);
	pthread_mutex_init(&chrono->eat_check, NULL);
	chrono->ph->num_ph = ft_atol(av[1]);
	chrono->time_to_die = ft_atol(av[2]);
	chrono->time_to_eat = ft_atol(av[3]);
	chrono->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		chrono->num_x_ph_must_eat = ft_atol(av[5]);
	else
		chrono->num_x_ph_must_eat = 0;
	chrono->are_all_alive = 1;
	chrono->start_time = get_time();
	print_struct(chrono);//
	init_ph(chrono);
}
