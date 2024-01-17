/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:53:47 by castorga          #+#    #+#             */
/*   Updated: 2024/01/16 19:47:58 by castorga         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

// --------- CHRONOGRAM STRUCT -----------
typedef struct s_chrono
{
	long long		start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_x_eat;//num por comer(arg. opcional)
	char			its_alive;
	unsigned int	q_philos;//cant.total phs
	pthread_mutex_t	mutex_meal;
	pthread_mutex_t	mutex_iter;
	pthread_mutex_t	*forks;
	t_philo			*ph;
}	t_chrono;

// --------- PHILOSOPHER STRUCT -----------
struct s_philo
{
	unsigned int	num_ph;//id del ph
	pthread_mutex_t	mutex_ph;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	size_t			last_eat;
	size_t			number_of_meals;
	t_chrono		*chrono_ph;
};


// ------------------------ Prototypes ------------------------ //
int			parsing(int ac, char *av[]);
void		init_chrono(t_chrono *chrono, char *av[]);
long		ft_atol(const char *str);
int			contains_digit(char *c);
int			philos_creation(t_chrono *chrono);
long long	get_time(t_chrono *ch);
int			ft_free(t_chrono *ch);
void		ph_eats(t_philo *ph);

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define FORK 5
#endif
