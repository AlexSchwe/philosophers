/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/07 02:38:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		check_arg(int argc, char **argv, t_args *args)
{
	t_var var;

	var.round = -1;
	if (argc < 4 || argc > 6)
		return (write(2, NB_ARGS, ft_strlen(NB_ARGS)));
	if ((var.nb = ft_atoi(argv[1])) < 2)
		return (write(2, NB_PHILO_ERROR, ft_strlen(NB_PHILO_ERROR)));
	if ((var.time_die = ft_atoi(argv[2])) <= 0)
		return (write(2, TIME_ERROR, ft_strlen(TIME_ERROR)));
	if ((var.time_eat = ft_atoi(argv[3])) <= 0)
		return (write(2, EAT_ERROR, ft_strlen(EAT_ERROR)));
	if ((var.time_sleep = ft_atoi(argv[4])) <= 0)
		return (write(2, SLEEP_ERROR, ft_strlen(SLEEP_ERROR)));
	if (argv[5] && ((var.round = ft_atoi(argv[5])) <= 0))
		return (write(2, ROUND_ERROR, ft_strlen(ROUND_ERROR)));
	var.start = get_time();
	args->var = var;
	args->pids = NULL;
	return (0);
}

void	start_semaphores(t_args *args)
{
	int	i;

	unlink_previous_semaphores(args);
	args->var.forks = open_new_semaphore("/forks", args->var.nb);
	if (!args->var.forks)
		clear(args, "Failed to open semaphore : forks");
	args->var.channel = open_new_semaphore("/channel", 1);
	if (!args->var.channel)
		clear(args, "Failed to open semaphore : channel");
	args->var.alive = open_new_semaphore("/alive", 0);
	if (!args->var.alive)
		clear(args, "Failed to open semaphore : alive");
	i = -1;
	while (++i < args->var.nb)
	{
		args->philo[i].var = args->var;
		args->philo[i].state = open_new_semaphore(args->philo[i].name, 1);
		if (!args->philo[i].state)
			clear(args, "Failed to open semaphore : state");
	}
}

/*
*** wait for the actions, that never return before the process is killed
*/

void	create_thread(t_args *args, int i)
{
	args->philo[i].last_time = get_time_since_start(args->var);
	display_action(&args->philo[i], "before thread\n");
	pthread_create(&args->philo[i].action, NULL, &philo_life,
				&args->philo[i]);
	pthread_create(&args->philo[i].control, NULL, &philo_control,
			&args->philo[i]);
	pthread_join(args->philo[i].action, NULL);
}

void	start_processes(t_args *args)
{
	int		i;
	pid_t	*pids;

	if (!(pids = malloc((args->var.nb) * sizeof(pid_t))))
		return ;
	i = -1;
	args->pids = pids;
	args->var.start = get_time();
	while (++i < args->var.nb)
	{
		if ((pids[i] = fork()) < 0)
			return ;
		if (pids[i] == 0)
			create_thread(args, i);
		usleep(100);
	}
	start_monitoring(args);
}

int		set_philosophers(t_args *args)
{
	int	i;

	i = -1;
	if (!(args->philo = malloc(sizeof(t_philo) * args->var.nb)))
		return (1);
	while (++i < args->var.nb)
	{
		if (!memset(&args->philo[i], 0, sizeof(t_philo)))
			return (1);
		args->philo[i].name = ft_itoa(i + 1);
	}
	return (0);
}
