/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 03:00:59 by geldiss           #+#    #+#             */
/*   Updated: 2021/04/11 14:29:49 by geldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_status(unsigned long time, char *msg, t_index *index, int number)
{
	if (sem_wait(g_philo->sem_print))
	{
		while (number)
		{
			sem_post(g_philo->forks);
			number--;
		}
		return (0);
	}
	printf("%lu %d %s\n", time, index->philo_i, msg);
	sem_post(g_philo->sem_print);
	return (1);
}

void	action_time(unsigned long start, unsigned long end)
{
	while ((get_time() - start) < end)
		usleep(100);
}

int	ft_eating(t_index *index)
{
	sem_wait(g_philo->forks);
	if (!(ft_status(get_time() - g_philo->time_begin, "has taken a fork",
				index, 1)))
		return (0);
	sem_wait(g_philo->forks);
	if (!(ft_status(get_time() - g_philo->time_begin, "has taken a fork",
				index, 2)))
		return (0);
	g_philo->time_last_eat = get_time();
	if (!(ft_status(get_time() - g_philo->time_begin, "is eating", index, 2)))
		return (0);
	action_time(get_time(), g_philo->info->time_to_eat);
	sem_post(g_philo->forks);
	sem_post(g_philo->forks);
	return (1);
}

void	protection(unsigned long i, int index)
{
	if (index % 2 == 0 && i == 1)
		usleep(100);
}

void	*ft_life(void *index)
{
	t_index			ind;
	unsigned long	i;
	pthread_t		brain;

	i = 0;
	ind = *((t_index *)index);
	g_philo->info->death_trigger = ind.philo_i;
	g_philo->time_last_eat = get_time();
	pthread_create(&brain, NULL, dead_or_alive, NULL);
	while (++i)
	{
		protection(i, ind.philo_i);
		if (!ft_eating(&ind))
			exit(-1);
		if (i == g_philo->info->philo_eat_number)
			break ;
		if (!(ft_status(get_time() - g_philo->time_begin, "is sleeping", &ind,
					0)))
			exit(-1);
		action_time(get_time(), g_philo->info->time_to_sleep);
		if (!(ft_status(get_time() - g_philo->time_begin, "is thinking", &ind,
					0)))
			exit(-1);
	}
	exit(0);
}
