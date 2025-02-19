/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:48:26 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:41:10 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief The philo sleeps
 *
 * @param philo The philo structure
 *
 * @note This function is called when the philo is either
 * 		sleeping or thinking
 */
void	*life(void *p)
{
	t_philo *const		philo = p;
	t_philo_ctx *const	ctx = philo->ctx;

	if (philo->id % 2)
		philo_sleep(philo, 4);
	while (is_running(ctx))
	{
		eat(philo);
		if (!is_running(philo->ctx))
			break ;
		philog(ctx, philo->id, ACTION_SLEEP);
		philo_sleep(philo, ctx->timers.sleep);
		philog(ctx, philo->id, ACTION_THINK);
	}
	return (NULL);
}
