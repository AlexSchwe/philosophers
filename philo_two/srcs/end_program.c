/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by lemarabe          #+#    #+#             */
/*   Updated: 2020/11/07 02:38:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	destroy_semaphores(t_args *args, int nb_philo)
{
	int	i;

	sem_unlink("/forks");
	if (args->var.forks)
		sem_close(args->var.forks);
	if (nb_philo)
	{
		sem_unlink("/channel");
		if (args->var.channel)
			sem_close(args->var.channel);
		if (nb_philo > 1)
		{
			i = -1;
			while (++i < nb_philo)
			{
				sem_unlink(args->philo[i].name);
				if ((args->philo[i].state))
					sem_close(args->philo[i].state);
			}
		}
	}
}

int		clear(t_args *args, char *str)
{
	int i;

	i = -1;
	destroy_semaphores(args, args->var.nb);
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