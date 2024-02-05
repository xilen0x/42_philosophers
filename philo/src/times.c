
#include "philo.h"

// long long	diff_time(long long start, long long current)
// {
// 	return (current - start);
// }

/*Return time in miliseconds*/
long long	get_time()
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

/*int	ph_to_die_time(t_philo *ph)//threads access
{
	long long	cu_time;
	long long	ttd;
	int			i;

	i = 0;
	ttd = ph->pchrono_ph->time_to_die;
	cu_time = get_time(ph->pchrono_ph);
	//while (1)
	while (ph->pchrono_ph->its_alive)
	{
		//if (diff_time(ph[i].last_eat, get_time(ph->pchrono_ph)) >= ttd)
		if (diff_time(cu_time, get_time(ph->pchrono_ph)) >= ttd)
		{
			ph->pchrono_ph->its_alive = 0;
			//printf("ph_to_die_time function\n");
			return (1);
		}
		//usleep(1000);
		i++;
	}
	return (0);
}*/

/*void	ph_sleep_time(t_philo *ph)//threads access
{
	long long	cu_time;
	long long	tts;

	tts = ph->pchrono_ph->time_to_sleep;
	cu_time = get_time(ph->pchrono_ph);
	while (1)
	{
		if (diff_time(cu_time, get_time(ph->pchrono_ph)) >= tts)
			break ;
		//usleep(1000);
	}
}*/

/*void	ph_eats_time(t_philo *ph)//threads access
{
	long long	cu_time;
	long long	tte;

	tte = ph->pchrono_ph->time_to_eat;
	cu_time = get_time(ph->pchrono_ph);
	while (1)
	{
		if (diff_time(cu_time, get_time(ph->pchrono_ph)) >= tte)
		{
			//printf("ph_eats_time function\n");
			break ;
		}
		//usleep(1000);
	}
}
*/
