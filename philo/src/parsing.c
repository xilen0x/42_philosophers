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

/*---------- CHECK if DIGITS ----------*/
int	check_digits(int ac, char *av[])
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Digito no valido!\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

//---------- CHECK RANGE ----------
int	check_range(int ac, char *av[])
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < 0)
		{
			printf("Fuera del rango\n");
			return (1);
		}
		i++;
	}
	return (0);
}

/*------------------ PARSING ------------------*/
int	parsing(int ac, char *av[])
{
	if (ac == 5 || ac == 6)
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
	}
	else
	{
		printf("Incorrect number of arguments!\n");
		printf("Ex: 1 200 250 100 5\n");
		return (1);
	}
	return (0);
}
