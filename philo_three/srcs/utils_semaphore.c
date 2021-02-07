/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_semaphore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/07 02:38:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	destroy_semaphores(t_args *args)
{
	int	i;

	sem_unlink("/forks");
	if (args->var.forks)
		sem_close(args->var.forks);
	sem_unlink("/channel");
	if (args->var.channel)
		sem_close(args->var.channel);
	sem_unlink("/alive");
	if (args->var.alive)
		sem_close(args->var.alive);
	sem_unlink("/prio");
	if (args->var.prio)
		sem_close(args->var.prio);
	if (args->var.nb > 1)
	{
		i = -1;
		while (++i < args->var.nb)
		{
			sem_unlink(args->philo[i].name);
			if ((args->philo[i].state))
				sem_close(args->philo[i].state);
		}
	}
}

char	*semaphore_name(char *number)
{
	char	*sem_name;
	int		i;

	if (!(sem_name = malloc(sizeof(char) * (ft_strlen(number) + 1) + 1)))
		return (NULL);
	sem_name[0] = '/';
	i = -1;
	while (number[++i] && i < 8)
		sem_name[i + 1] = number[i];
	sem_name[i + 1] = '\0';
	free(number);
	return (sem_name);
}

sem_t	*open_new_semaphore(char *name, int value)
{
	sem_t	*sem;

	if (!name)
		return (NULL);
	if (!(sem = sem_open(name, O_CREAT | O_EXCL, 0600, value)))
		return (NULL);
	return (sem);
}
