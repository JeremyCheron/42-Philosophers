/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:28:23 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:43:05 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Get the current time in milliseconds
 *
 * @return The current time in milliseconds
 */
static time_t	_get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

/**
 * @brief Convert a string to a time_t
 *
 * @param str The string to convert
 * @param time The value to store the result
 *
 * @return 1 if the conversion was successful, 0 otherwise
 */
int	ft_atotime(const char *str, time_t *time)
{
	time_t	_time;

	if (*str == '\0')
		return (0);
	_time = 0;
	while (*str >= '0' && *str <= '9')
	{
		_time *= 10;
		_time += *str - '0';
		++str;
	}
	*time = _time;
	return (*str == '\0');
}

/**
 * @brief Convert a string to an unsigned integer
 *
 * @param str The string to convert
 * @param value The value to store the result
 *
 * @return 1 if the conversion was successful, 0 otherwise
 */
int	ft_atoui(const char *str, unsigned int *value)
{
	unsigned int	_value;

	if (*str == '\0')
		return (0);
	_value = 0;
	while (*str >= '0' && *str <= '9')
	{
		_value *= 10;
		_value += *str - '0';
		++str;
	}
	*value = _value;
	return (*str == '\0');
}

/**
 * @brief Get the current time in milliseconds
 *
 * @return The current time in milliseconds
 */
time_t	ft_time_ms(void)
{
	static time_t	initial_time = -1;
	const time_t	current_time = _get_current_time();

	if (initial_time == -1)
		initial_time = current_time;
	return (current_time - initial_time);
}
