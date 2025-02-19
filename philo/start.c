/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:35:45 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:42:30 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Wait for all threads to finish
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called to wait for all threads to finish
 */
static void	_wait_thread(t_philo_ctx *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->philo_count)
	{
		if (ctx->philos[i].thread_id != 0)
			pthread_join(ctx->philos[i].thread_id, NULL);
		i++;
	}
}

/**
 * @brief Check if a philo has eaten enough
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called to check if a philo has eaten enough
 * 		times if the number of lunch param was given
 */
static void	_check_each(t_philo_ctx *ctx)
{
	size_t			i;
	unsigned int	times_eaten;

	i = 0;
	while (i < ctx->philo_count && ctx->timers.each != __INT_MAX__)
	{
		pthread_mutex_lock(&ctx->philos[i].mutex_eaten);
		times_eaten = ctx->philos[i].times_eat;
		pthread_mutex_unlock(&ctx->philos[i].mutex_eaten);
		if (times_eaten < (unsigned int)ctx->timers.each)
			break ;
		i++;
	}
	if (i == ctx->philo_count)
		set_running(ctx, false);
}

/**
 * @brief Check if a philo is dead
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called to check if a philo is dead
 */
static void	_die(t_philo_ctx *ctx)
{
	size_t	i;
	time_t	time_since_eat;

	while (is_running(ctx))
	{
		i = 0;
		while (i < ctx->philo_count)
		{
			pthread_mutex_lock(&ctx->philos[i].mutex_eating);
			time_since_eat = ft_time_ms() - ctx->philos[i].last_time_eat;
			if (time_since_eat >= ctx->timers.death)
			{
				set_running(ctx, false);
				philog(ctx, i, ACTION_DIE);
				pthread_mutex_unlock(&ctx->philos[i].mutex_eating);
				break ;
			}
			pthread_mutex_unlock(&ctx->philos[i].mutex_eating);
			i++;
		}
		_check_each(ctx);
	}
}

/**
 * @brief Start the program
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called at the beginning of the program
 *		to start it
 */
void	start(t_philo_ctx *ctx)
{
	size_t	i;

	ctx->is_running = true;
	i = 0;
	while (i < ctx->philo_count)
	{
		ctx->philos[i].last_time_eat = ft_time_ms();
		if (pthread_create(&ctx->philos[i].thread_id, NULL,
				life, &ctx->philos[i]))
		{
			set_running(ctx, false);
			_wait_thread(ctx);
			error(ctx, ERR_THRAD_INIT);
		}
		usleep(500);
		i++;
	}
	_die(ctx);
	_wait_thread(ctx);
}
