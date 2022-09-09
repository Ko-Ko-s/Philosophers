/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:46:56 by geldiss           #+#    #+#             */
/*   Updated: 2021/04/11 22:17:13 by geldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*dead_or_alive(void *what)
{
	unsigned long	time;
	unsigned long	last_time;

	what = NULL;
	(void)what;
	while (1)
	{
		time = get_time();
		last_time = g_philo->time_last_eat;
		usleep(100);
		if (time > last_time && (time - last_time)
			> g_philo->info->time_to_die)
		{
			sem_post(g_philo->sem_print);
			sem_close(g_philo->sem_print);
			exit(g_philo->info->death_trigger);
		}
	}
}

void	extermination(pthread_t *threads, t_index *index, int i)
{
	int	status;

	waitpid(-1, &status, 0);
	sem_close(g_philo->forks);
	if (WEXITSTATUS(status) > 0)
		printf("%lu %d %s\n", get_time() - g_philo->time_begin,
			WEXITSTATUS(status), "died");
	else
	{
		while (i--)
			waitpid(-1, &status, 0);
	}
	sem_close(g_philo->sem_print);
	exit_free(index, threads);
	kill(0, SIGINT);
}

int	start(void)
{
	pthread_t		*threads;
	int				i;
	t_index			*index;
	pid_t			process;

	if (!all_init(&index, &threads))
		return (ft_print_error("Memory error\n", EXIT_FAILURE));
	i = 0;
	g_philo->time_begin = get_time();
	while (i < g_philo->info->philo_number)
	{
		process = fork();
		if (process == 0)
			ft_life(&(index[i]));
		i++;
	}
	extermination(threads, index, i);
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
