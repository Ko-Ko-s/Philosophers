/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:46:56 by geldiss           #+#    #+#             */
/*   Updated: 2021/04/11 22:22:47 by geldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	dead_or_alive(void)
{
	unsigned long	time;
	unsigned long	last_time;
	int				i;

	while (1)
	{
		usleep(100);
		i = g_philo->info->philo_number;
		while (i--)
		{
			time = get_time();
			last_time = g_philo->time_last_eat[i];
			if (time > last_time && g_philo->info->death_trigger == -1
				&& (time - last_time) > g_philo->info->time_to_die)
			{
				g_philo->info->death_trigger = i + 1;
				g_philo->info->time_of_death = time - g_philo->time_begin;
				sem_post(g_philo->sem_print);
				sem_close(g_philo->sem_print);
				return ;
			}
			if (g_philo->info->end == 1)
				return ;
		}
	}
}

int	start(void)
{
	pthread_t		*threads;
	int				i;
	t_index			*index;

	if (!all_init(&index, &threads))
		return (ft_print_error("Memory error\n", EXIT_FAILURE));
	i = 0;
	g_philo->time_begin = get_time();
	while (i < g_philo->info->philo_number)
	{
		g_philo->time_last_eat[i] = get_time();
		pthread_create(&threads[i], NULL, ft_life, &index[i]);
		i++;
	}
	dead_or_alive();
	while (i--)
		pthread_join(threads[i], NULL);
	sem_close(g_philo->forks);
	if (g_philo->info->death_trigger >= 0)
		printf("%lu %d %s\n", g_philo->info->time_of_death,
			g_philo->info->death_trigger, "died");
	sem_close(g_philo->sem_print);
	exit_free(index, threads);
	return (0);
}

void	input_info(t_info *info, char **argv)
{
	info->philo_number = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 5 && argc != 6)
		return (ft_print_error("Wrong number of arguments\n", EXIT_FAILURE));
	if (!correct_input(argc, argv))
		return (ft_print_error("Wrong input\n", EXIT_FAILURE));
	if (argv[5])
	{
		if (ft_atoi(argv[5]) < 1)
			return (ft_print_error("Error for philo eat times\n", 1));
		info.philo_eat_number = ft_atoi(argv[5]);
	}
	else
		info.philo_eat_number = -1;
	input_info(&info, argv);
	g_philo = malloc(sizeof(t_philo));
	if (!(g_philo))
		return (ft_print_error("Malloc error\n", EXIT_FAILURE));
	g_philo->info = &info;
	return (start());
}
