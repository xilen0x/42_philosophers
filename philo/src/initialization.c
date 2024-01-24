/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 18:59:15 by castorga          #+#    #+#             */
/*   Updated: 2024/01/24 17:31:34 by castorga         ###   ########.fr       */
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
	if (pthread_mutex_init(&ch->pph->mutex_last_eat, NULL) && \
		pthread_mutex_init(&ch->pph->mutex_nbr_of_meals, NULL) && \
		pthread_mutex_init(&ch->pph->mutex_msgs, NULL) && \
		pthread_mutex_init(ch->pph->pmutex_right_fork, NULL) && \
		pthread_mutex_init(ch->pph->pmutex_left_fork, NULL) && \
		pthread_mutex_init(&ch->mutex_its_alive, NULL))
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
	ch->pph = NULL;
	ch->pforks = NULL;
	ch->pph = (t_philo *)malloc(sizeof(t_philo) * ch->q_philos);
	ch->pforks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ch->q_philos);
	if (!(ch->pph) || !(ch->pforks))
		ft_free(ch);
	pthread_mutex_init(ch->pforks, NULL);
	while (i < ch->q_philos)
	{
		ch->pph[i].pchrono_ph = ch;
		ch->pph[i].num_ph = i + 1;
		ch->pph[i].last_eat = 0;
		ch->pph->pmutex_left_fork = &ch->pforks[i];

		if (i == ch->q_philos)//si es el ultimo Ph
			ch->pph->pmutex_right_fork = &ch->pforks[0];
		else
			ch->pph->pmutex_right_fork = &ch->pforks[i + 1];
		ch->pph[i].number_of_meals = 0;
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
