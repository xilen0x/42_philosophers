/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:53:47 by castorga          #+#    #+#             */
/*   Updated: 2024/02/15 19:38:50 by castorga         ###   ########.fr       */
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

typedef struct s_philo	t_philo;

// ------------------------ CHRONOGRAM STRUCT ----------- //
typedef struct s_chrono
{
	long long		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_x_eat;
	int				its_alive;
	int				q_philos;
	int				opt;
	pthread_mutex_t	mutex_times;
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
	//pthread_mutex_t	mutex_actions;
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
long long	get_current_time(t_chrono *ch);
long		ft_atol(const char *str);
int			ft_atoi(const char *str);
int			contains_digit(char *c);
void		print_struct(t_chrono *chrono);
void		init_other_mutexes(t_chrono *ch);
int			philos_creation(t_chrono *chrono);
void		ph_eats(t_philo *ph);
void		ph_msgs(t_philo *ph, char *msg);
int			monitor(t_chrono *chrono);
int			destroy(t_chrono *ch);
int			get_its_alive(t_chrono *ch);
void		set_its_alive(t_chrono *ch);
long long	get_last_eat(t_philo *ph);
int			check_digits(int ac, char *av[]);
int			check_range(int ac, char *av[]);
int			ft_usleep(t_chrono *ch, size_t milliseconds);
int			get_number_of_meals(t_philo *ph);
int			ft_isdigit(char num);
#endif
