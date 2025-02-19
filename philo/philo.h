/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:03:13 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:46:40 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ERR_BAD_ALLOC 1
#define ERR_NAT_INT "must be a natural integer"
#define ERR_NULL "cannot be null"
#define ERR_MUTEX "mutex init error"
#define ERR_ALLOC "Bad alloc"
#define ERR_THRAD_INIT "Thread init error"

#define PHILO "number_of_philosophers"
#define DIE "time_to_die"
#define EAT "time_to_eat"
#define SLEEP "time_to_sleep"
#define LUNCH "number_of_times_each_philosopher_must_eat"

#define FORK_TAKEN "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DIED "died"

typedef enum e_args
{
	PROG_NAME,
	PHILO_COUNT,
	DEATH_TIMER,
	EAT_TIMER,
	SLEEP_TIMER,
	EACHP_TIMER,
	PROG_MIN=SLEEP_TIMER + 1,
	PROG_MAX=EACHP_TIMER + 1
}	t_args;

typedef enum e_action
{
	ACTION_TAKE_FORK,
	ACTION_EAT,
	ACTION_SLEEP,
	ACTION_THINK,
	ACTION_DIE
}	t_action;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				id;
	bool			is_dead;
	unsigned int	times_eat;
	time_t			last_time_eat;
	pthread_mutex_t	mutex_eating;
	pthread_mutex_t	mutex_eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	void			*ctx;
}	t_philo;

typedef struct s_philo_ctx
{
	char			*program;
	unsigned int	philo_count;
	bool			is_running;
	pthread_mutex_t	mutex_is_running;
	struct s_timers
	{
		time_t			death;
		time_t			eat;
		time_t			sleep;
		unsigned int	each;
	}				timers;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
}	t_philo_ctx;

void	destroy(
			t_philo_ctx *ctx);

void	eat(
			t_philo *philo);

void	error(
			t_philo_ctx *ctx,
			const char *message);

void	usage(void);

void	init(
			t_philo_ctx *ctx);

void	init_args(
			t_philo_ctx *ctx,
			int ac,
			char **av);

void	*life(
			void *p);

void	set_running(
			t_philo_ctx *ctx,
			bool running);

bool	is_running(
			t_philo_ctx *ctx);

void	philog(
			t_philo_ctx *ctx,
			int id,
			t_action action);

void	philo_sleep(
			t_philo *philo,
			time_t duration);

void	start(
			t_philo_ctx *ctx);

int		ft_atotime(
			const char *str,
			time_t *time);

int		ft_atoui(
			const char *str,
			unsigned int *value);

time_t	ft_time_ms(void);
