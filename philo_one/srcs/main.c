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

#include "philo_one.h"

void	*philo_control(void *arg)
{
	t_philo			*philo;
	unsigned long	time_death;

	philo = (t_philo *)arg;
	philo->death += philo->var.time_die;
	time_death = get_time_since_start(philo->var);
	while (*philo->var.quit)
	{
		time_death = get_time_since_start(philo->var);
		pthread_mutex_lock(&philo->state);
		if (philo->death >= time_death)
		{
			pthread_mutex_unlock(&philo->state);
			usleep(philo->death - time_death);
		}
		else
		{
			display_action(philo, DEATH);
			*philo->var.quit = 0;
			pthread_mutex_unlock(&philo->state);
		}
	}
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->var.quit)
	{
		handle_fork(philo, philo->fork_right);
		handle_fork(philo, philo->fork_left);
		handle_eat(philo);
		if (philo->var.round-- == 0 && *philo->var.quit > 0)
			*philo->var.quit -= 1;
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

int		main(int argc, char **argv)
{
	t_args *args;

	if (!(args = malloc(sizeof(t_args))))
		return (1);
	args = memset(args, 0, sizeof(t_args));
	if (check_arg(argc, argv, args))
		return (1);
	set_philosophers(args);
	start_mutexes(args);
	start_threads(args);
	wait_for_all_threads(args);
	clear(args, "");
	return (0);
}
