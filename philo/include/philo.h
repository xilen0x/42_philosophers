/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:53:47 by castorga          #+#    #+#             */
/*   Updated: 2024/01/25 12:29:10 by castorga         ###   ########.fr       */
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
	int				its_alive;
	int				q_philos;//cant.total phs
	pthread_mutex_t	mutex_its_alive;
	pthread_mutex_t	*pforks;
	t_philo			*pph;
}	t_chrono;

// ------------------------ PHILOSOPHER STRUCT ----------- //
struct s_philo
{
	int				num_ph;//id del ph
	long long		last_eat;
	int				number_of_meals;
	pthread_mutex_t	mutex_msgs;
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	mutex_nbr_of_meals;
	pthread_mutex_t	*pmutex_left_fork;
	pthread_mutex_t	*pmutex_right_fork;
	pthread_t		thread;//var q almacenará a c/hilo
	t_chrono		*pchrono_ph;
};

// ------------------------ Prototypes -------------------- //
int			parsing(int ac, char *av[]);
void		init_chrono(t_chrono *chrono, char *av[]);
long long	get_time(void);
long long	diff_time(long long start, long long current);
long		ft_atol(const char *str);
int			ft_atoi(const char *str);
int			contains_digit(char *c);
int			ft_free(t_chrono *ch);
void		print_struct(t_chrono *chrono);
void		init_other_mutexes(t_chrono *ch);
int			philos_creation(t_chrono *chrono);
void		ph_eats(t_philo *ph);
void		ph_msgs(t_philo *ph, int n);
int			monitor(t_chrono *chrono);
void		ph_sleep(t_philo *ph);
//void		set_number_of_meals(t_philo *ph);
//void		set_last_eat(t_philo *ph);
int			destroy(t_chrono *ch);

#endif
