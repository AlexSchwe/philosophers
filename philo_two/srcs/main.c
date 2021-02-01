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
#include "philo_two.h"

void	*philo_control(void *arg)
{
	t_philo			*philo;
	unsigned long	time_death;

	philo = (t_philo *)arg;
	philo->death += philo->var.time_die;
	while (*philo->quit)
	{
		time_death = get_time_since_start(philo->var);
		sem_wait(philo->state);
		if (philo->death >= time_death)
		{
			sem_post(philo->state);
			usleep(2000);
		}
		else
		{
			philo->last_time = time_death;
			display_action(philo, DEATH);
			*philo->quit = 0;
			sem_post(philo->state);
		}
	}
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->quit)
	{
		handle_fork(philo);
		handle_fork(philo);
		sem_wait(philo->state);
		philo->death = philo->last_time + philo->var.time_die;
		sem_post(philo->state);
		handle_eat(philo);
		if (philo->var.round-- == 0 && *philo->quit > 0)
		{

			*philo->quit -= 1;
		}

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
	if (check_arg(argc, argv, args))
		return (clear(args, 1));
	set_philosophers(args);
	start_semaphores(args);
	start_threads(args);
	wait_for_all_threads(args);
	clear(args, 1);
	return (0);
}