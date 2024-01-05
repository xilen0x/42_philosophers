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
typedef enum e_ph_status
{
	THINKING,
	HUNGRY,
	EATING,
	SLEEPING
}	t_ph_status;

typedef struct s_philo
{
	unsigned int	num_ph;
	unsigned int	rigth_i_ph;
	unsigned int	left_i_ph;
	long long		last_eat;
	unsigned int	num_ph_eaten;
	struct s_crono	*crono_ph;
	//pthread_mutex_t	fork;
}	t_philo;

typedef struct s_crono
{
	unsigned int	num_ph;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_x_ph_must_eat;
	long long		start;
	//int			everyone_alive;
	//pthread_mutex_t	writing;
	//pthread_mutex_t	eat_check;
	t_philo			*ph;
} t_crono;

int			parsing(int ac, char *av[]);
void		init_crono(t_crono *crono, char *av[]);
long		ft_atol(const char *str);
int			contains_digit(char *c);
long long	get_time(void);

#endif
