/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:26:10 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:46:52 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Initialize the philos
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called at the beginning of the program
 *		to initialize the philos
 */
static void	_init_philos(t_philo_ctx *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		ctx->philos[i].r_fork = &ctx->forks[(i + 1) % ctx->philo_count];
		ctx->philos[i].l_fork = &ctx->forks[i];
		ctx->philos[i]. id = i;
		ctx->philos[i].last_time_eat = 0;
		ctx->philos[i].times_eat = 0;
		ctx->philos[i].ctx = ctx;
		ctx->philos[i].thread_id = 0;
		if (pthread_mutex_init(&ctx->philos[i].mutex_eating, NULL)
			|| pthread_mutex_init(&ctx->philos[i].mutex_eaten, NULL))
			error(ctx, ERR_MUTEX);
		ctx->philos[i++].is_dead = 0;
	}
}

/**
 * @brief Initialize the forks
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called at the beginning of the program
 * 		to initialize the forks
 */
static void	_init_forks(t_philo_ctx *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->philo_count)
		if (pthread_mutex_init(&ctx->forks[i++], NULL))
			break ;
	if (i == ctx->philo_count)
		return ;
	while (i--)
		pthread_mutex_destroy(&ctx->forks[i]);
}

/**
 * @brief Initialize the arguments of the program
 *
 * @param ctx The philo_ctx structure
 * @param ac The number of arguments
 * @param av The arguments
 *
 * @note This function is called at the beginning of the program
 *		to initialize the arguments
 */
void	init_args(t_philo_ctx *ctx, int ac, char **av)
{
	unsigned int *const	each = &ctx->timers.each;

	ctx->program = av[PROG_NAME];
	ctx->philos = NULL;
	ctx->is_running = false;
	ctx->forks = NULL;
	if (!ft_atoui(av[PHILO_COUNT], &ctx->philo_count))
		error(ctx, PHILO " " ERR_NAT_INT);
	if (!ft_atotime(av[DEATH_TIMER], &ctx->timers.death))
		error(ctx, DIE " " ERR_NAT_INT);
	if (!ft_atotime(av[EAT_TIMER], &ctx->timers.eat))
		error(ctx, EAT " " ERR_NAT_INT);
	if (!ft_atotime(av[SLEEP_TIMER], &ctx->timers.sleep))
		error(ctx, SLEEP " " ERR_NAT_INT);
	if (ac == PROG_MAX && !ft_atoui(av[EACHP_TIMER], each))
		error(ctx, LUNCH " " ERR_NAT_INT);
	if (ac != PROG_MAX)
		*each = __INT_MAX__;
	if (ctx->philo_count == 0)
		error(ctx, PHILO " " ERR_NULL);
	if (pthread_mutex_init(&ctx->mutex_is_running, NULL))
		error(ctx, ERR_MUTEX);
}

/**
 * @brief Initialize the philo_ctx structure
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called at the beginning of the program
 */
void	init(t_philo_ctx *ctx)
{
	ctx->forks = malloc(sizeof(*ctx->forks) * ctx->philo_count);
	if (ctx->forks == NULL)
		error(ctx, ERR_ALLOC);
	_init_forks(ctx);
	ctx->philos = malloc(sizeof(*ctx->philos) * ctx->philo_count);
	if (ctx->philos == NULL)
		error(ctx, ERR_ALLOC);
	_init_philos(ctx);
}
