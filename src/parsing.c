/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:27:04 by castorga          #+#    #+#             */
/*   Updated: 2024/02/07 15:26:53 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Parsing function */
int	parsing(int ac, char *av[])
{
	if (ac == 5 || ac == 6)
	{
		if (check_digits(ac, av))
		{
			write (2, "Error\n", 6);
			return (1);
		}
		if (check_range(ac, av))
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
