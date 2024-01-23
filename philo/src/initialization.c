/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:59:15 by castorga          #+#    #+#             */
/*   Updated: 2024/01/23 18:34:12 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*print struct - borrar luego*/
void	print_struct(t_chrono *chrono)
{
	printf("start_time: %lld\n", chrono->start_time);
	printf("q_philos: %u\n", chrono->q_philos);
	printf("time_to_die: %d\n", chrono->time_to_die);
	printf("time_to_eat: %d\n", chrono->time_to_eat);
	printf("time_to_sleep: %d\n", chrono->time_to_sleep);
	printf("num_x_eat: %d\n", chrono->num_x_eat);
}

/*Initialization of all mutexes*/
void	init_other_mutexes(t_chrono *ch)
{
	if (pthread_mutex_init(&ch->ph->mutex_last_eat, NULL) && \
		pthread_mutex_init(&ch->ph->mutex_nbr_of_meals, NULL) && \
		pthread_mutex_init(&ch->ph->mutex_msgs, NULL))
	{
		printf("Error initializing mutex\n");
		return ;
	}
}

/*Initialization of the philosophers structure(t_philo)*/
static int	init_ph(t_chrono *ch)
{
	int	i;

	i = 0;
	ch->ph = NULL;
	ch->forks = NULL;
	ch->ph = (t_philo *)malloc(sizeof(t_philo) * ch->q_philos);
	ch->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ch->q_philos);
	if (!(ch->ph) || !(ch->forks))
		ft_free(ch);
	pthread_mutex_init(ch->forks, NULL);
	while (i < ch->q_philos)
	{
		ch->ph[i].chrono_ph = ch;
		ch->ph[i].num_ph = i + 1;
		ch->ph[i].last_eat = 0;
		ch->ph->mutex_left_fork = &ch->forks[i];

		if (i == ch->q_philos)//si es el ultimo ph
			ch->ph->mutex_right_fork = &ch->forks[0];
		else
			ch->ph->mutex_right_fork = &ch->forks[i + 1];
		ch->ph[i].number_of_meals = 0;
		i++;
	}
	init_other_mutexes(ch);
	return (0);
}

/*Initialization of the chronogram structure(t_chrono)*/
void	init_chrono(t_chrono *ch, char *av[])
{
	ch->start_time = get_time();
	ch->q_philos = ft_atoi(av[1]);
	ch->time_to_die = ft_atoi(av[2]);
	ch->time_to_eat = ft_atoi(av[3]);
	ch->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		ch->num_x_eat = ft_atoi(av[5]);
	else
		ch->num_x_eat = 0;
	ch->its_alive = 1;
	//print_struct(ch);
	init_ph(ch);
}
