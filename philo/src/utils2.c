/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:12:52 by castorga          #+#    #+#             */
/*   Updated: 2024/01/31 18:28:38 by castorga         ###   ########.fr       */
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

long long	diff_time(long long start, long long current)
{
	// printf("STARTS %lld CURRENT %lld\n", start, current);
	// printf("RES %lld\n",  current - start);
	return (current - start);
}

/*Return time in miliseconds*/
long long	get_time(t_chrono *ch)
{
	struct timeval	tv;

	pthread_mutex_lock(&ch->mutex_times);
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	pthread_mutex_unlock(&ch->mutex_times);
}
