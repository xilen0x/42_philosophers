/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:33:50 by castorga          #+#    #+#             */
/*   Updated: 2024/01/12 17:45:13 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
//printf("%lld %u is eating\n", chrono->start_time, chrono->ph->num_ph);

//fn x saber el status de c/philo

//fn x hacer q c/philo coma
void	ph_eats(t_philo *ph)
{
	printf("teste2\n");//aki voy - ver pq no se imprime los 2 printf de abajo!!!!!!!!!!
	pthread_mutex_lock(&ph->mutex_ph);
	//printf("%lld %u has taken a fork\n", (get_time() - ph->chrono_ph->start_time), ph->num_ph);
	//printf("%lld %u has taken a fork\n", get_time() - ph->chrono_ph->start_time, ph->num_ph);
	pthread_mutex_unlock(&ph->mutex_ph);

}

//fn monitor
void	*monitor(t_philo *ph)
{
	while (ph->chrono_ph->are_all_alive)
	{
		ph_eats(ph);
		//if (comido == xcomer || !are_all_alive)
		//	break ;

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
	//printf("QQTT:: %u\n", chrono->q_philos);
	philosopher = (pthread_t *)malloc(sizeof(pthread_t) * chrono->q_philos);
	if (!philosopher)
		return (1);
	while (i < chrono->q_philos)
	{
		//printf("%u\n", i);
		if (pthread_create(&philosopher[i], NULL, (void *)monitor, &chrono->ph[i]))
		{
			printf("Error creating thread\n");
			return (1);
		}
		chrono->ph[i].last_eat = get_time();
		i++;
	}
	// i = 0;
	// while (i < chrono->q_philos)
	// {
		// pthread_join(philosopher[i], NULL);
		// i++;
	// }
	return (0);
}
