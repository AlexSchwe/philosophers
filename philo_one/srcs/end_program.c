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

#include "philo_one.h"

void	destroy_mutexes(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->var.nb)
	{
		pthread_mutex_unlock(&args->philo[i].state);
		pthread_mutex_unlock(&args->forks[i]);
		pthread_mutex_destroy(&args->philo[i].state);
		pthread_mutex_destroy(&args->forks[i]);
	}
	pthread_mutex_unlock(&args->var.channel);
	pthread_mutex_destroy(&args->var.channel);
}

int		clear(t_args *args, char *str)
{
	int i;

	i = -1;
	destroy_mutexes(args);
	if (args->var.quit)
		free(args->var.quit);
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
