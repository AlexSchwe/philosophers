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

#include "philo_one.h"

void	wait_for_all_threads(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->philo[i].control, NULL);
	i = -1;
	while (++i < args->nb_philo)
		pthread_join(args->philo[i].thread, NULL);
}

void	destroy_mutexes(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_mutex_unlock(&args->philo[i].state);
		pthread_mutex_unlock(&args->forks[i]);
		pthread_mutex_destroy(&args->philo[i].state);
		pthread_mutex_destroy(&args->forks[i]);
	}
	pthread_mutex_unlock(&args->channel);
	pthread_mutex_destroy(&args->channel);
}

int		clean_and_exit(t_args *args, int to_free, char *str)
{
	int	i;

	if (to_free)
	{
		if (to_free > 1)
		{
			i = -1;
			while (++i < args->nb_philo)
				free(args->philo[i].name);
			free(args->philo);
		}
		free(args->forks);
	}
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(0);
}
