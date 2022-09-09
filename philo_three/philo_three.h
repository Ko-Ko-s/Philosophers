/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geldiss <geldiss@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:47:01 by geldiss           #+#    #+#             */
/*   Updated: 2021/04/11 14:32:20 by geldiss          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_info
{
	unsigned long	time_of_death;
	int				death_trigger;
	int				philo_number;
	unsigned long	philo_eat_number;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	unsigned long	time_to_sleep;
}					t_info;

typedef struct s_philo
{
	t_info			*info;
	unsigned long	time_begin;
	unsigned long	time_last_eat;
	sem_t			*sem_print;
	sem_t			*forks;
}					t_philo;

typedef struct s_index
{
	int				philo_i;
	int				rfork_i;
}					t_index;

t_philo				*g_philo;
int					ft_print_error(char *msg, int ret);
int					correct_input(int argc, char **argv);
int					ft_atoi(const char *str);
int					all_init(t_index **index, pthread_t **threads);
void				exit_free(t_index *index, pthread_t *threads);
unsigned long		get_time(void);
void				*ft_life(void *index);
void				*dead_or_alive(void *what);
#endif
