/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:59:15 by castorga          #+#    #+#             */
/*   Updated: 2024/02/15 13:23:20 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Initialization of all mutexes*/
void	init_other_mutexes(t_chrono *ch)
{
	int	i;

	i = 0;
	while (i < ch->q_philos)
	{
		if (pthread_mutex_init(&ch->pph[i].mutex_last_eat, NULL) && \
			pthread_mutex_init(&ch->pph[i].mutex_nbr_of_meals, NULL))
			//pthread_mutex_init(ch->pph[i].pmutex_left_fork, NULL) && 
			//pthread_mutex_init(ch->pph[i].pmutex_right_fork, NULL))
		{
			printf("Error initializing mutex\n");
			return ;
		}
		i++;
	}
	pthread_mutex_init(&ch->mutex_its_alive, NULL);
}

/*Initialization of the philosophers structure(t_philo)*/
static int	init_ph(t_chrono *ch)
{
	int	i;

	ch->pforks = NULL;
	ch->pforks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ch->q_philos);
	if (!(ch->pforks))
	{
		free(ch->pforks);
		return (1);
	}
	i = 0;
	while (i < ch->q_philos)
		pthread_mutex_init(&ch->pforks[i++], NULL);
	i = 0;
	while (i < ch->q_philos)
	{
		ch->pph[i].pchrono_ph = ch;
		ch->pph[i].num_ph = i + 1;
		ch->pph[i].last_eat = 0;
		ch->pph[i].pmutex_left_fork = &ch->pforks[i];
		if (i == (ch->q_philos) - 1)//si es el ultimo Ph
			ch->pph[i].pmutex_right_fork = &ch->pforks[0];
		else
			ch->pph[i].pmutex_right_fork = &ch->pforks[i + 1];
		ch->pph[i].number_of_meals = 0;
		i++;
	}
	init_other_mutexes(ch);
	return (0);
}

/*Initialization of the chronogram structure(t_chrono)*/
void	init_chrono(t_chrono *ch, char *av[])
{
	ch->pph = NULL;

	pthread_mutex_init(&ch->mutex_times, NULL);
	ch->start_time = get_time();//
	ch->q_philos = ft_atoi(av[1]);
	ch->time_to_die = ft_atoi(av[2]);
	ch->time_to_eat = ft_atoi(av[3]);
	ch->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		ch->num_x_eat = ft_atoi(av[5]);
	else
		ch->num_x_eat = 0;
	ch->its_alive = 1;
	ch->pph = (t_philo *)malloc(sizeof(t_philo) * ch->q_philos);
	if (!(ch->pph))
	{
		free(ch->pph);
		return ;
	}
	init_ph(ch);
}
