/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:27:04 by castorga          #+#    #+#             */
/*   Updated: 2024/01/03 19:27:05 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
/* 
number_of_philosophers 		time_to_die 		time_to_eat 		time_to_sleep[number_of_times_each_philosopher_must_eat]
		1 200 250 100 5 
*/

/*---------- CHECK DIGITS ----------*/
int	ft_check_digits(int ac, char *av[])
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_contains_digit(av[i]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*---------- CHECK RANGE AV ----------*/
int	ft_check_range(int ac, char *av[])
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

/*---------- CHECK DUPLICATES ----------*/
int	ft_check_duplic(int ac, char *av[])
{
	int	i;
	int	j;

	i = 1;
	j = i + 1;
	while (i < ac)
	{
		while (j < ac)
		{
			if (ft_atol(av[i]) == ft_atol(av[j]))
				return (1);
			j++;
		}
		i++;
		j = i + 1;
	}
	return (0);
}

/*------------------ CHECKS ------------------*/
int	parsing(int ac, char *av[])
{
	if (check_digits(ac, av))
	{
		write (2, "Error\n", 6);
		return (1);
	}
	else if (check_range(ac, av))
	{
		write (2, "Error\n", 6);
		return (1);
	}
	else if (check_negative(ac, av))
	{
		write (2, "Error\n", 6);
		return (1);
	}
	return (0);
}
