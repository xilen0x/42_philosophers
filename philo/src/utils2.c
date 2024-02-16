/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:12:52 by castorga          #+#    #+#             */
/*   Updated: 2024/02/15 19:37:33 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	contains_digit(char *c)
{
	while (*c)
	{
		if (ft_isdigit(*c) && *c != ' ' && *c != '\"')
			return (1);
		c++;
	}
	return (0);
}

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
				printf("Not valid digit!\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_range(int ac, char *av[])
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < 0)
		{
			printf("Out of range!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_isspace(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	return (str);
}

int	ft_atoi(const char *str)
{
	short int	parity;
	int			number;
	char		*mystr;

	parity = 0;
	number = 0;
	mystr = ft_isspace((char *)str);
	if (*mystr == '+' || *mystr == '-')
	{
		if (*mystr == '-')
			parity++;
		mystr++;
	}
	while (*mystr >= '0' && *mystr <= '9')
	{
		number *= 10;
		number += *mystr - '0';
		mystr++;
	}
	if (parity % 2 == 0)
		return (number);
	return (-number);
}
