/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:09:02 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:40:46 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Print a message about the philo
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called when the philo is doing an action
 */
void	philog(t_philo_ctx *ctx, int id, t_action action)
{
	static pthread_mutex_t	mut = PTHREAD_MUTEX_INITIALIZER;
	const char				*actions[] = {
	[ACTION_TAKE_FORK] = "has taken a fork",
	[ACTION_EAT] = "is eating",
	[ACTION_SLEEP] = "is sleeping",
	[ACTION_THINK] = "is thinking",
	[ACTION_DIE] = "died",
	};

	pthread_mutex_lock(&mut);
	if (is_running(ctx) || action == ACTION_DIE)
		printf("%-8ld%d %s\n", ft_time_ms(), id, actions[action]);
	pthread_mutex_unlock(&mut);
}

/**
 * @brief Check if the program is running
 *
 * @param ctx The philo_ctx structure
 *
 * @return true if the program is running, false otherwise
 */
bool	is_running(t_philo_ctx *ctx)
{
	bool	is_running;

	pthread_mutex_lock(&ctx->mutex_is_running);
	is_running = ctx->is_running;
	pthread_mutex_unlock(&ctx->mutex_is_running);
	return (is_running);
}

/**
 * @brief Set the program to running or not
 *
 * @param ctx The philo_ctx structure
 * @param running The value to set
 */
void	set_running(t_philo_ctx *ctx, bool running)
{
	pthread_mutex_lock(&ctx->mutex_is_running);
	ctx->is_running = running;
	pthread_mutex_unlock(&ctx->mutex_is_running);
}
