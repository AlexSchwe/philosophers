/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/07 02:38:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		clear(t_args *args, char *str)
{
	int i;

	i = -1;
	if (args->pids)
		free(args->pids);
	unlink_previous_semaphores(args);
	if (args->philo)
	{
		while (++i < args->var.nb)
			free(args->philo[i].name);
		free(args->philo);
	}
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(0);
}
