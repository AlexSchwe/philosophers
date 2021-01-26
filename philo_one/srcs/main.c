/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/07 02:38:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_one.h"

void	*philo_control(void *arg)
{
	t_philo	*philo;
	unsigned long time_death;

	philo = (t_philo *)arg;
	philo->death += philo->var.time_die;
	while (*philo->quit)
	{
		time_death = get_time_since_start(philo->var);
		pthread_mutex_lock(&philo->state);
		if (philo->death >= time_death)
		{
			pthread_mutex_unlock(&philo->state);
			usleep(2000);
		}
		else
		{
			philo->last_time = time_death;
			display_action(philo, DEATH);
			*philo->quit = 0;
			pthread_mutex_unlock(&philo->state);
		}
	}
	return (NULL);
}

void	handle_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->state);
	display_action(philo, EAT);
	sleep_philo(philo, philo->var.time_eat);
	pthread_mutex_unlock(&philo->state);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void handle_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	philo->last_time = get_time_since_start(philo->var);
	display_action(philo, FORK);
}

void handle_sleep(t_philo *philo)
{
	display_action(philo, SLEEP);
	sleep_philo(philo, philo->var.time_sleep);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->quit)
	{
		handle_fork(philo, philo->fork_right);
		handle_fork(philo, philo->fork_left);
		pthread_mutex_lock(&philo->state);
		philo->death = philo->last_time + philo->var.time_die;
		pthread_mutex_unlock(&philo->state);
		handle_eat(philo);
		if (philo->var.round-- == 0 && *philo->quit > 0)
			*philo->quit -= 1;
		handle_sleep(philo);
		display_action(philo, THINK);
	}
	return (NULL);
}

void	wait_for_all_threads(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->var.nb)
		pthread_join(args->philo[i].control, NULL);
	i = -1;
	while (++i < args->var.nb)
		pthread_join(args->philo[i].action, NULL);
}

int main(int argc, char **argv)
{
	t_args *args;

	if (!(args = malloc(sizeof(t_args))))
		return (1);
	if (check_arg(argc, argv, args))
		return (clear(args, 1));
	set_philosophers(args);
	start_mutexes(args);
	start_threads(args);
	wait_for_all_threads(args);
	clear(args, 0);
	return (0);
}