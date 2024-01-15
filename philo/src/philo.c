/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/15 14:12:38 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
//printf("%lld %u is eating\n", chrono->start_time, chrono->ph->num_ph);

//fn x saber el status de c/philo

//fn x hacer q c/philo coma
void	ph_eats(t_philo *ph)
{
	pthread_mutex_lock(&ph[ph->left_fork].mutex_ph);
	printf("%lld %u has taken a fork A\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);//modif. luego el msg

	pthread_mutex_lock(&ph[ph->rigth_fork].mutex_ph);
	printf("%lld %u has taken a fork B\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);

	pthread_mutex_lock(&ph->chrono_ph->mutex_chrono);
	printf("%lld %u  is eating\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);

	ph->times_ate++;
	ph->last_eat = get_time();
	pthread_mutex_unlock(&ph->chrono_ph->mutex_chrono);
	//ft_sleep(table->time_to_eat);
	pthread_mutex_unlock(&ph[ph->rigth_fork].mutex_ph);
	pthread_mutex_unlock(&ph[ph->left_fork].mutex_ph);

}

//fn monitor
void	*monitor(t_philo *ph)
{
	if (ph->num_ph % 2)
		usleep(50);
	while (ph->chrono_ph->are_all_alive)
	{
		ph_eats(ph);
		if ((ph->chrono_ph->ph->times_ate == ph->chrono_ph->num_x_eat) || !(ph->chrono_ph->are_all_alive))
			break ;

		//state(philo, SLEEP);
		//ft_sleep(chrono->time_to_sleep);
		//state(philo, THINK);
	}
	return (NULL);
}

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
		i++;
	}
	i = 0;
	/*while (i < chrono->q_philos)
	{
		pthread_join(philosopher[i], NULL);
		i++;
	}*/
	return (0);
}
