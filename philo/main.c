/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:07:02 by jcheron           #+#    #+#             */
/*   Updated: 2025/02/19 09:43:51 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief check the arguments of the program and run it
 *
 * @param ac The number of arguments
 * @param av The arguments
 *
 * @return int The exit status
 */
int	main(int ac, char **av)
{
	t_philo_ctx	ctx;

	if (ac < PROG_MIN || ac > PROG_MAX)
		usage();
	init_args(&ctx, ac, av);
	init(&ctx);
	ft_time_ms();
	start(&ctx);
	destroy(&ctx);
	return (EXIT_SUCCESS);
}
