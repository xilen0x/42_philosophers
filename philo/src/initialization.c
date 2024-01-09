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
void	print_struct(struct s_crono *crono)
{
	printf("num_ph: %d\n", crono->num_ph);
	printf("time_to_die: %d\n", crono->time_to_die);
	printf("time_to_eat: %d\n", crono->time_to_eat);
	printf("time_to_sleep: %d\n", crono->time_to_sleep);
	printf("num_x_ph_must_eat: %d\n", crono->num_x_ph_must_eat);
	printf("num_x_ph_must_eat: %lld\n", crono->start);
}

/*Inicializacion de mis philosofos(threads)*/
void	init_ph(t_chrono *chrono)
{
	unsigned int	i;

	i = 0;
	chrono->ph = NULL;
	chrono->ph = malloc(sizeof(t_philo) * chrono->num_ph);
	if (!chrono)
	{
		printf("Error reserving memory!\n");
		free(chrono);
		return ;
	}
	while (i < chrono->num_ph)
	{
		chrono->ph[i].chrono_ph = chrono;
		chrono->ph[i].num_ph = i + 1;
		chrono->ph[i].last_eat = 0;
		chrono->ph[i].rigth_fork = i + 1;
		chrono->ph[i].left_fork = i;
		i++;
	}
}

/*Inicializacion de la estructura*/
void	init_chrono(t_chrono *chrono, char *av[])
{
	chrono->num_ph = ft_atol(av[1]);
	chrono->time_to_die = ft_atol(av[2]);
	chrono->time_to_eat = ft_atol(av[3]);
	chrono->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		chrono->num_x_ph_must_eat = ft_atol(av[5]);
	else
		chrono->num_x_ph_must_eat = 0;
	chrono->start_time = get_time();
	print_struct(chrono);
	init_ph(chrono);
}
