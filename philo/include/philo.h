/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: castorga <castorga@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:53:47 by castorga          #+#    #+#             */
/*   Updated: 2024/01/03 16:53:49 by castorga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

// ------------------------ Structs ------------------------ //
/*typedef struct s_stack
{
	int				num;
	struct s_stack	*next;
}	t_stack;
*/

int		parsing(int ac, char *av[]);
//int	ft_isdigit(int num);
long	ft_atol(const char *str);
int		contains_digit(char *c);

#endif
