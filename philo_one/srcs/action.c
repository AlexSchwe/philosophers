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

#include "philo_one.h"

void	handle_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->state);
	display_action(philo, EAT);
	sleep_philo(philo, philo->var.time_eat);
	pthread_mutex_unlock(&philo->state);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	handle_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
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
	pthread_mutex_lock(&philo->var.channel);
	write(1, buffer, i);
	if (ft_strcmp(action, DEATH))
		pthread_mutex_unlock(&philo->var.channel);
}
