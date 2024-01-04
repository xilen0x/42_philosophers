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
	printf("num_x_ph_must_eat: %lld\n", crono->start);//aqui voy
}

/*Inicializacion de la estructura*/
void	init_crono(struct s_crono *crono, char *av)
{
	crono->num_ph = ft_atol(&av[1]);
	crono->time_to_die = ft_atol(&av[2]);
	crono->time_to_eat = ft_atol(&av[3]);
	crono->time_to_sleep = ft_atol(&av[4]);
	if (&av[5])
		crono->num_x_ph_must_eat = ft_atol(&av[5]);
	else
		crono->num_x_ph_must_eat = 0;
	crono->start = get_time();
	print_struct(crono);
}
