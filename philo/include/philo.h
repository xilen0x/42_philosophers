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
	pthread_t		id_thread;
	size_t			num_ph;
	size_t			rigth_fork;
	size_t			left_fork;
	long long		last_eat;
	size_t			times_ate;
	pthread_mutex_t	fork;
	struct s_chrono	*chrono_ph;
}	t_philo;

typedef struct s_chrono
{
	long long		start_time;
	size_t			num_ph;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_x_ph_must_eat;
	size_t			are_all_alive;
	pthread_mutex_t	writing;
	pthread_mutex_t	eat_check;
	t_philo			*ph;
}	t_chrono;

// ------------------------ Prototypes ------------------------ //
int			parsing(int ac, char *av[]);
void		init_chrono(t_chrono *chrono, char *av[]);
long		ft_atol(const char *str);
int			contains_digit(char *c);
long long	get_time(void);

#endif
