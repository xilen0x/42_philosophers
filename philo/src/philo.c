/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/16 12:34:06 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	are_all_alive(t_philo *ph)
{
	size_t	i;

	i = 0;
	while ((ph->chrono_ph->are_all_alive) && i < ph->chrono_ph->q_philos)
	{
		pthread_mutex_lock(&ph->chrono_ph->mutex_chrono);
		if ((ph->last_eat - get_time()) < ph->chrono_ph->time_to_die)
		{
			printf("%lld %u died\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);
			ph->chrono_ph->are_all_alive = 0;
		}
		pthread_mutex_unlock(&ph->chrono_ph->mutex_chrono);
		if (!(ph->chrono_ph->are_all_alive))
			break ;
	}
}

void	go_to_sleep(t_philo *ph)
{
	usleep(100);
	printf("%lld %u  is sleeping\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);
}

void	ph_eats(t_philo *ph)
{
	pthread_mutex_lock(&ph[ph->left_fork].mutex_ph);
	printf("%lld %u has taken a fork\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);

	pthread_mutex_lock(&ph[ph->rigth_fork].mutex_ph);
	printf("%lld %u has taken a fork\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);

	pthread_mutex_lock(&ph->chrono_ph->mutex_chrono);
	printf("%lld %u is eating\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);

	ph->number_of_meals++;
	ph->last_eat = get_time();
	pthread_mutex_unlock(&ph->chrono_ph->mutex_chrono);
	pthread_mutex_unlock(&ph[ph->rigth_fork].mutex_ph);
	pthread_mutex_unlock(&ph[ph->left_fork].mutex_ph);
}

//Function monitor - Manage the threads
void	*monitor(t_philo *ph)
{
	if (ph->num_ph % 2)
		usleep(100);
	while (ph->chrono_ph->are_all_alive)
	{
		ph_eats(ph);
		if ((ph->chrono_ph->ph->number_of_meals == ph->chrono_ph->num_x_eat) || !(ph->chrono_ph->are_all_alive))
			break ;
		go_to_sleep(ph);
		printf("%lld %u  is thinking\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);
	}
	are_all_alive(ph);
	return (NULL);
}

//Function to create threads
int	philos_creation(t_chrono *chrono)
{
	pthread_t		*philosopher;
	unsigned int	i;

	i = 0;
	philosopher = (pthread_t *)malloc(sizeof(pthread_t) * chrono->q_philos);
	if (!philosopher)
		return (1);
	while (i < chrono->q_philos)
	{
		if (pthread_create(&philosopher[i], NULL, (void *)monitor, &chrono->ph[i]))
		{
			printf("Error creating thread\n");
			return (1);
		}
		chrono->ph[i].last_eat = get_time();
		//pthread_join(philosopher[i], NULL);
		i++;
	}
	i = 0;
	while (i < chrono->q_philos)
	{
		pthread_join(philosopher[i], NULL);
		i++;
	}
	return (0);
}
