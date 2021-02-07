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
	philo->death = get_time_since_start(philo->var) + philo->var.time_die;
	pthread_mutex_unlock(&philo->state);
	display_action(philo, EAT);
	sleep_philo(philo->var.time_eat);
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
	sleep_philo(philo->var.time_sleep);
}

int		ft_write_nb(char *buf, unsigned long u)
{
	unsigned long	nb;
	size_t			size;
	size_t			i;

	nb = u;
	size = 0;
	while (1)
	{
		size++;
		if (!(nb /= 10))
			break ;
	}
	i = size;
	while (1)
	{
		buf[--i] = '0' + (u % 10);
		if (!(u /= 10))
			break ;
	}
	return (size);
}

/*
*** Affiche l'action via un seul write,
*** pour limiter les appels sytèmes (syscalls)
*/

void	display_action(t_philo *philo, char *action)
{
	char	buffer[SIZE_BUFF];
	int		i;
	char	*to_print;

	pthread_mutex_lock(&philo->var.channel);
	i = ft_write_nb(buffer, get_time_since_start(philo->var));
	buffer[i] = ' ';
	to_print = philo->name;
	while (*to_print)
		buffer[++i] = *to_print++;
	buffer[++i] = ' ';
	while (*action)
		buffer[++i] = *action++;
	buffer[++i] = '\n';
	if (*philo->var.quit)
		write(1, buffer, i);
	if (ft_strcmp(action, DEATH))
		pthread_mutex_unlock(&philo->var.channel);
}
