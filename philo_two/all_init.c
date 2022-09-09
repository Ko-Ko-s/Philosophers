/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 01:42:23 by geldiss           #+#    #+#             */
/*   Updated: 2021/04/11 22:22:21 by geldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	init(pthread_t **threads, t_index **index)
{
	int	i;

	g_philo->time_last_eat = malloc(sizeof(unsigned long)
			* g_philo->info->philo_number);
	if (!(g_philo->time_last_eat))
		return (0);
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
		(*index)[i].philo_i = i + 1;
		i++;
	}
	(*index)[i].rfork_i = i;
	(*index)[i].philo_i = i + 1;
	return (1);
}

int	init_sem(void)
{
	sem_unlink("Sem_write");
	sem_unlink("Sem_fork");
	g_philo->sem_print = sem_open("Sem_write", O_CREAT, 0777, 1);
	if ((g_philo->sem_print == SEM_FAILED))
		return (0);
	g_philo->forks = sem_open("Sem_fork", O_CREAT, 0777,
			g_philo->info->philo_number);
	if ((g_philo->forks == SEM_FAILED))
		return (0);
	return (1);
}

void	exit_free(t_index *index, pthread_t *threads)
{
	if (index != NULL)
		free(index);
	if (threads != NULL)
		free(threads);
	if (g_philo->time_last_eat != NULL)
		free(g_philo->time_last_eat);
	sem_unlink("Sem_write");
	sem_unlink("Sem_fork");
	free(g_philo);
}

int	all_init(t_index **index, pthread_t **threads)
{
	*index = NULL;
	*threads = NULL;
	g_philo->sem_print = NULL;
	g_philo->time_last_eat = NULL;
	g_philo->forks = NULL;
	g_philo->info->end = 0;
	g_philo->info->death_trigger = -1;
	if (!init(threads, index) || !init_sem())
	{
		exit_free(*index, *threads);
		return (0);
	}
	return (1);
}
