/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:51:59 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:37:08 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Destroy all mutexes and free all allocated memory
 *
 * @param ctx The philo_ctx structure
 *
 * @note This function is called at the end of the program
 */
void	destroy(t_philo_ctx *ctx)
{
	size_t	i;

	pthread_mutex_destroy(&ctx->mutex_is_running);
	if (ctx->forks == NULL)
		return ;
	i = 0;
	while (i < ctx->philo_count)
		pthread_mutex_destroy(&ctx->forks[i++]);
	free(ctx->forks);
	if (ctx->philos == NULL)
		return ;
	i = 0;
	while (i < ctx->philo_count)
	{
		pthread_mutex_destroy(&ctx->philos[i].mutex_eating);
		pthread_mutex_destroy(&ctx->philos[i].mutex_eaten);
		i++;
	}
	free(ctx->philos);
}
