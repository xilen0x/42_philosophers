/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:53:47 by castorga          #+#    #+#             */
/*   Updated: 2024/01/22 12:58:09 by castorga         ###   ########.fr       */
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
# include <limits.h>

// ------------------------ Macros ------------------------ //
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define FORK 5


typedef struct s_philo	t_philo;

// ------------------------ CHRONOGRAM STRUCT ----------- //
typedef struct s_chrono
{
	long long		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_x_eat;//num por comer(arg. opcional)
	char			its_alive;
	int	q_philos;//cant.total phs
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	mutex_nbr_of_meals;
	pthread_mutex_t	*forks;
	t_philo			*ph;
}	t_chrono;

// ------------------------ PHILOSOPHER STRUCT ----------- //
struct s_philo
{
	int				num_ph;//id del ph
	pthread_mutex_t	mutex_msgs;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long long		last_eat;
	int				number_of_meals;
	t_chrono		*chrono_ph;
};

// ------------------------ Prototypes -------------------- //
int			parsing(int ac, char *av[]);
void		init_chrono(t_chrono *chrono, char *av[]);
void		init_other_mutexes(t_chrono *ch);
long		ft_atol(const char *str);
int			contains_digit(char *c);
int			philos_creation(t_chrono *chrono);
//long long	get_time(t_chrono *ch);
long long	get_time(void);
int			ft_free(t_chrono *ch);
void		ph_eats(t_philo *ph);
void		ph_msgs(t_philo *ph, int n);
int			did_anyone_die(t_chrono *chrono);
long long	difference_of_time(long long start, long long current);
void		ph_sleep(long long time);
#endif
