/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:05:47 by castorga          #+#    #+#             */
/*   Updated: 2024/02/14 14:18:50 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;
	long long		res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (res);
}

long long	get_current_time(t_chrono *ch)
{
	struct timeval	tv;
	long long		res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (res - ch->start_time);
}

int	ft_usleep(t_chrono *ch, size_t milliseconds)
{
	size_t	start;

	start = get_current_time(ch);
	while ((get_current_time(ch) - start) < milliseconds)
		usleep(500);
	return (0);
}
