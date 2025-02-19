/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:44:34 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:38:27 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Print an error message and exit the program
 *
 * @param ctx The philo_ctx structure
 * @param message The error message
 *
 * @note This function is called when an error occurs
 */
void	error(t_philo_ctx *ctx, const char *message)
{
	dprintf(STDERR_FILENO, "%s: %s\n", ctx->program, message);
	destroy(ctx);
	exit(EXIT_FAILURE);
}

/**
 * @brief Print the usage of the program and exit
 */
void	usage(void)
{
	printf("Usage: ./philo " PHILO " " DIE " " EAT " " SLEEP " (" LUNCH ")\n");
	exit(EXIT_SUCCESS);
}
