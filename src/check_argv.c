/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:43:54 by castorga          #+#    #+#             */
/*   Updated: 2023/09/04 17:43:56 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/philo.h"

//---------- CHECK DIGITS ----------
/*int	ft_check_digits(int ac, char *av[])
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

//---------- CHECK RANGE AV ----------
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

//---------- CHECK DUPLICATES ----------
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

int	ft_check_argv_are_valid(int ac, char *av[])
{
	if (av[1][0] == '\0' || av[1][0] == ' ')
	{
		write (2, "Error\n", 6);
		return (1);
	}
	if (ft_check_digits(ac, av) == 1)
	{
		write (2, "Error\n", 6);
		return (1);
	}
	else if (ft_check_range(ac, av) == 1)
	{
		write (2, "Error\n", 6);
		return (1);
	}
	else if (ft_check_duplic(ac, av) == 1)
	{
		write (2, "Error\n", 6);
		return (1);
	}
	return (0);
}
*/