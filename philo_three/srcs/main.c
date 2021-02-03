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

#include "philo_three.h"

void	start_monitoring(t_args *args)
{
	int i;

	i = -1;

	while (++i < args->var.nb)
		sem_wait(args->var.alive);
	i = -1;
	while (++i < args->var.nb)
		kill(args->pids[i], SIGKILL);
}

//faire un quit pour bloquer l'affichage
void	*philo_control(void *arg)
{
	t_philo			*philo;
	unsigned long	time_death;
	int				i;

	philo = (t_philo *)arg;
	philo->death += philo->var.time_die;
	time_death = get_time_since_start(philo->var);
	while (philo->death >= time_death)
	{
		time_death = get_time_since_start(philo->var);
		sem_post(philo->state);
		usleep(1000);
		sem_wait(philo->state);
	}
	philo->last_time = time_death;
	display_action(philo, DEATH);
	sem_post(philo->state);
	i = -1;
	while (++i < philo->var.nb)
		sem_post(philo->var.alive);
	return (NULL);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_time = get_time_since_start(philo->var);
	while (1)
	{
		handle_fork(philo);
		handle_fork(philo);
		sem_wait(philo->state);
		philo->death = philo->last_time + philo->var.time_die;
		sem_post(philo->state);
		handle_eat(philo);
		if (philo->var.round-- == 0)
			sem_post(philo->var.alive);
		handle_sleep(philo);
		display_action(philo, THINK);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_args *args;

	if (!(args = malloc(sizeof(t_args))))
		return (1);
	args = memset(args, 0, sizeof(t_args));
	if (check_arg(argc, argv, args))
		return (!clear(args, "wrong args"));
	set_philosophers(args);
	start_semaphores(args);
	start_processes(args);
	clear(args, "Les philosophes ont disparu");
	return (0);
}
