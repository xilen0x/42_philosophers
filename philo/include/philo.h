/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:53:47 by castorga          #+#    #+#             */
/*   Updated: 2024/01/03 16:53:49 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// ------------------------ Structs ------------------------ //
struct s_crono
{
	int	num_ph;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_x_ph_must_eat;
	long long	start;
};


int		parsing(int ac, char *av[]);
void	init_crono(struct s_crono *crono, char *av);
long	ft_atol(const char *str);
int		contains_digit(char *c);
long long	get_time(void);
#endif
