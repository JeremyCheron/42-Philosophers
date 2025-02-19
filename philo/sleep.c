/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:45:40 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/18 17:48:01 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo, time_t duration)
{
	time_t	now;

	now = ft_time_ms();
	while (now + duration > ft_time_ms())
	{
		if (!is_running(philo->ctx))
			break ;
		usleep(((t_philo_ctx *)philo->ctx)->philo_count * 2);
	}
}
