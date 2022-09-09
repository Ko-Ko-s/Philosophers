/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 01:42:23 by geldiss           #+#    #+#             */
/*   Updated: 2021/04/11 15:15:00 by geldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	init(pthread_t **threads, t_index **index)
{
	int	i;

	*threads = malloc(sizeof(pthread_t) * g_philo->info->philo_number);
	if (!(*threads))
		return (0);
	*index = malloc(sizeof(t_index) * g_philo->info->philo_number);
	if (!(*index))
		return (0);
	i = 0;
	while (i < (g_philo->info->philo_number - 1))
	{
		(*index)[i].rfork_i = i;
		(*index)[i].lfork_i = i + 1;
		(*index)[i].philo_i = i + 1;
		i++;
	}
	(*index)[i].rfork_i = i;
	(*index)[i].lfork_i = 0;
	(*index)[i].philo_i = i + 1;
	return (1);
}

int	fork_init(void)
{
	int	i;

	g_philo->forks = malloc(sizeof(pthread_mutex_t *)
			* g_philo->info->philo_number);
	if (!(g_philo->forks))
		return (0);
	i = 0;
	while (i < g_philo->info->philo_number)
	{
		g_philo->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!(g_philo->forks[i]))
		{
			g_philo->forks[i] = NULL;
			return (0);
		}
		i++;
	}
	while (i--)
		pthread_mutex_init(g_philo->forks[i], NULL);
	return (1);
}

int	mutex_init(void)
{
	g_philo->mutex_print = malloc(sizeof(pthread_mutex_t)
			* g_philo->info->philo_number);
	if (!(g_philo->mutex_print))
		return (0);
	g_philo->time_last_eat = malloc(sizeof(unsigned long)
			* g_philo->info->philo_number);
	if (!(g_philo->time_last_eat))
		return (0);
	if (!fork_init())
		return (0);
	pthread_mutex_init(g_philo->mutex_print, NULL);
	return (1);
}

void	exit_free(t_index *index, pthread_t *threads)
{
	int	i;

	if (index != NULL)
		free(index);
	if (threads != NULL)
		free(threads);
	if (g_philo->time_last_eat != NULL)
		free(g_philo->time_last_eat);
	i = 0;
	if (g_philo->forks != NULL)
	{
		while (i < g_philo->info->philo_number && g_philo->forks[i] != NULL)
		{
			pthread_mutex_destroy(g_philo->forks[i]);
			free(g_philo->forks[i]);
			i++;
		}
		free(g_philo->forks);
	}
	if (g_philo->mutex_print != NULL)
	{
		pthread_mutex_destroy(g_philo->mutex_print);
		free(g_philo->mutex_print);
	}
	free(g_philo);
}

int	all_init(t_index **index, pthread_t **threads)
{
	*index = NULL;
	*threads = NULL;
	g_philo->mutex_print = NULL;
	g_philo->time_last_eat = NULL;
	g_philo->forks = NULL;
	g_philo->info->end = 0;
	g_philo->info->death_trigger = -1;
	if (!init(threads, index) || !mutex_init())
	{
		exit_free(*index, *threads);
		return (0);
	}
	return (1);
}
