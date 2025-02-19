/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:56:31 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:38:10 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief The philo eats
 *
 * @param philo The philo structure
 *
 * @note This function is called when the philo is eating
 */
static void	_take_r_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	philog(philo->ctx, philo->id, ACTION_TAKE_FORK);
}

/**
 * @brief The philo eats
 *
 * @param philo The philo structure
 *
 * @note This function is called when the philo is eating
 */
static void	_take_l_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	philog(philo->ctx, philo->id, ACTION_TAKE_FORK);
}

/**
 * @brief The philo eats
 *
 * @param philo The philo structure
 *
 * @note This function is called when the philo is eating
 */
static void	_take_forks(t_philo *philo)
{
	const int	odd = philo->id % 2;

	if (odd)
		_take_r_fork(philo);
	_take_l_fork(philo);
	if (!odd && philo->l_fork != philo->r_fork)
		_take_r_fork(philo);
}

/**
 * @brief The philo eats
 *
 * @param philo The philo structure
 * @param time The time to sleep
 *
 * @note This function is called when the philo is eating
 */
void	eat(t_philo *philo)
{
	_take_forks(philo);
	if (philo->r_fork == philo->l_fork)
	{
		while (is_running(philo->ctx))
			usleep(50);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(&philo->mutex_eating);
	philog(philo->ctx, philo->id, ACTION_EAT);
	philo->last_time_eat = ft_time_ms();
	pthread_mutex_unlock(&philo->mutex_eating);
	philo_sleep(philo, ((t_philo_ctx *)philo->ctx)->timers.eat);
	pthread_mutex_unlock(&philo->mutex_eaten);
	++philo->times_eat;
	pthread_mutex_unlock(&philo->mutex_eaten);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
