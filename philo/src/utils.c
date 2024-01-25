/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:47:45 by castorga          #+#    #+#             */
/*   Updated: 2024/01/24 16:30:52 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#include <limits.h>

int	ft_free(t_chrono *ch)
{
	printf("Error reserving memory!\n");
	free(ch->pph);
	free(ch->pforks);
	return (0);
}

static char	*ft_isspace(char *str)
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

long	ft_atol(const char *str)
{
	int i;
	long res;
	int sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > (LONG_MAX - (str[i] - '0')) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}


int	ft_isdigit(char num)
{
	if (num >= '0' && num <= '9')
	{
		return (1);
	}
	return (0);
}

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
