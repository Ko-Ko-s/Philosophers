/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 16:35:11 by geldiss           #+#    #+#             */
/*   Updated: 2021/04/11 14:30:05 by geldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
			i++;
		else if (str[i] == '\n' || str[i] == '\r' || str[i] == '\f')
			i++;
		else
			return (i);
	}
	return (i);
}

static unsigned long	ft_count(const char *str, int j, int i, int sign)
{
	unsigned long	count;
	unsigned long	wall;

	count = 0;
	wall = (unsigned long)(LONG_MAX / 10);
	while (j < i)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			if ((count > wall || (count == wall && (str[j] - '0') > 7))
				&& sign == 1)
				return (-1);
			else if ((count > wall || (count == wall && (str[j] - '0') > 8))
				&& sign == -1)
				return (0);
			count = count * 10 + (str[j] - '0');
		}
		else
			return (count);
		j++;
	}
	return (count);
}

int	ft_atoi(const char *str)
{
	int				sign;
	int				j;
	int				k;
	unsigned long	nb;

	sign = 1;
	j = 0;
	k = 0;
	while (str[k] != '\0')
		k++;
	j = ft_isspace(str);
	if (str[j] == '-')
	{
		sign = -1;
		j++;
	}
	else if (str[j] == '+')
		j++;
	nb = ft_count(str, j, k, sign);
	return ((int)(nb * sign));
}
