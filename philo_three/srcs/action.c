/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/07 02:38:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	handle_eat(t_philo *philo)
{
	sem_wait(philo->state);
	display_action(philo, EAT);
	sleep_philo(philo, philo->var.time_eat);
	sem_post(philo->state);
	sem_post(philo->var.forks);
	sem_post(philo->var.forks);
}

void	handle_fork(t_philo *philo)
{
	philo->last_time = get_time_since_start(philo->var);
	display_action(philo, FORK);
}

void	handle_sleep(t_philo *philo)
{
	display_action(philo, SLEEP);
	sleep_philo(philo, philo->var.time_sleep);
}

/*
*** Affiche l'action via un seul write,
*** pour limiter les appels sytèmes (syscalls)
*/

void	display_action(t_philo *philo, char *action)
{
	char	*to_print;
	char	buffer[SIZE_BUFF];
	int		i;

	i = -1;
	to_print = ft_itoa(philo->last_time);
	while (to_print[++i])
		buffer[i] = to_print[i];
	buffer[i] = ' ';
	free(to_print);
	to_print = philo->name;
	while (*to_print)
		buffer[++i] = *to_print++;
	buffer[++i] = ' ';
	while (*action)
		buffer[++i] = *action++;
	buffer[++i] = '\n';
	sem_wait(philo->var.channel);
	write(1, buffer, i);
	if (ft_strcmp(action, DEATH))
		sem_post(philo->var.channel);
}
