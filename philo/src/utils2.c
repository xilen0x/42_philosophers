/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:12:52 by castorga          #+#    #+#             */
/*   Updated: 2024/01/19 13:13:34 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/philo.h"

long long	difference_of_time(long long start, long long current)
{
	return (current - start);
}

/*Return time in miliseconds*/
long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
