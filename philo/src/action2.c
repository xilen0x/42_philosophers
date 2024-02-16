/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:38:58 by castorga          #+#    #+#             */
/*   Updated: 2024/02/16 15:15:52 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//function GETTER that check the value of its_alive variable
int	get_its_alive(t_chrono *ch)
{
	int	alive;


	pthread_mutex_lock(&ch->mutex_its_alive);
	alive = ch->its_alive;
	pthread_mutex_unlock(&ch->mutex_its_alive);
	return (alive);
}

//function SETTER that change the its_alive variable
void	set_its_alive(t_chrono *ch)
{
	pthread_mutex_lock(&ch->mutex_its_alive);
	ch->its_alive = 0;
	pthread_mutex_unlock(&ch->mutex_its_alive);
}
