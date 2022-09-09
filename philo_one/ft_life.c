/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 03:00:59 by geldiss           #+#    #+#             */
/*   Updated: 2021/04/11 13:25:15 by geldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_status(unsigned long time, char *msg, t_index *index)
{
	if (pthread_mutex_lock(g_philo->mutex_print) != 0)
	{
		pthread_mutex_unlock(g_philo->forks[index->lfork_i]);
		pthread_mutex_unlock(g_philo->forks[index->rfork_i]);
		return (0);
	}
	printf("%lu %d %s\n", time, index->philo_i, msg);
	pthread_mutex_unlock(g_philo->mutex_print);
	return (1);
}

void	action_time(unsigned long start, unsigned long end)
{
	while ((get_time() - start) < end)
	{
		if (g_philo->info->death_trigger > 0)
			return ;
		usleep(100);
	}
}

int	ft_eating(t_index *index)
{
	if ((index->philo_i % 2) == 0)
		pthread_mutex_lock(g_philo->forks[index->lfork_i]);
	else
		pthread_mutex_lock(g_philo->forks[index->rfork_i]);
	if (!(ft_status(get_time() - g_philo->time_begin, "has taken a fork",
				index)))
		return (0);
	if ((index->philo_i % 2) == 0)
		pthread_mutex_lock(g_philo->forks[index->rfork_i]);
	else
		pthread_mutex_lock(g_philo->forks[index->lfork_i]);
	if (!(ft_status(get_time() - g_philo->time_begin, "has taken a fork",
				index)))
		return (0);
	g_philo->time_last_eat[index->rfork_i] = get_time();
	if (!(ft_status(get_time() - g_philo->time_begin, "is eating", index)))
		return (0);
	action_time(get_time(), g_philo->info->time_to_eat);
	pthread_mutex_unlock(g_philo->forks[index->rfork_i]);
	pthread_mutex_unlock(g_philo->forks[index->lfork_i]);
	return (1);
}

void	*ft_life(void *index)
{
	t_index			ind;
	unsigned long	i;

	i = 0;
	ind = *((t_index *)index);
	while (++i)
	{
		if (!ft_eating(&ind))
			return (0);
		if (i == g_philo->info->philo_eat_number)
			break ;
		if (!(ft_status(get_time() - g_philo->time_begin, "is sleeping", &ind)))
			return (0);
		action_time(get_time(), g_philo->info->time_to_sleep);
		if (!(ft_status(get_time() - g_philo->time_begin, "is thinking", &ind)))
			return (0);
	}
	g_philo->info->end = 1;
	return (0);
}
