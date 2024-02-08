/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:05:47 by castorga          #+#    #+#             */
/*   Updated: 2024/02/07 19:11:02 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Returns the current time in milliseconds from a reference point.*/
long long	get_time(void)
{
	struct timeval	tv;
	long long		res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (res);
}

/*Gets the current time in milliseconds from a specified starting point 
stored in a t_chrono structure.*/
long long	get_current_time(t_chrono *ch)
{
	struct timeval	tv;
	long long		res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (res - ch->start_time);
}

/*Pauses execution for a specified number of milliseconds.*/
int	ft_usleep(t_chrono *ch, size_t milliseconds)
{
	size_t	start;

	start = get_current_time(ch);
	while ((get_current_time(ch) - start) < milliseconds)
		usleep(500);
	return (0);
}
