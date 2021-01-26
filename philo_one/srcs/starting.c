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

#include "philo_one.h"

int		check_arg(int argc, char **argv, t_args *args)
{
	t_var var;

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
	if (!(args->forks = malloc(sizeof(pthread_mutex_t) * var.nb)))
		return (write(2, strerror(errno), ft_strlen(strerror(errno))));
	var.start = get_time();
	args->var = var;
	return (0);
}

void	start_mutexes(t_args *args)
{
	int	i;
	int nb;

	nb = args->var.nb;
	pthread_mutex_init(&args->channel, NULL);
	i = -1;
	while (++i < args->var.nb)
	{
		pthread_mutex_init(&args->forks[(i + nb - 1) % nb], NULL);
		pthread_mutex_init(&args->philo[i].state, NULL);
		pthread_mutex_init(&args->philo[i].death_time, NULL);
	}
}

void	create_thread(t_args *args, int i)
{
	pthread_create(&args->philo[i].action, NULL, &philo_life,
				&args->philo[i]);
	pthread_create(&args->philo[i].control, NULL, &philo_control,
			&args->philo[i]);
}

void	start_threads(t_args *args)
{
	int	i;

	i = -1;
	args->var.start = get_time();
	while (++i < args->var.nb)
	{
		if (!(i % 2))
		{
			create_thread(args, i);
		}
	}
	usleep(args->var.time_eat);
	while (--i)
	{
		if (i % 2)
		{
			create_thread(args, i);
		}
	}
}

int		set_philosophers(t_args *args)
{
	int	i;

	i = -1;
	printf("entree set_philosophers\n");
	if (!(args->philo = malloc(sizeof(t_philo) * args->var.nb)))
		return (1);
	while (++i < args->var.nb)
	{
		if (!memset(&args->philo[i], 0, sizeof(t_philo)))
			return (1);
		args->philo[i].name = ft_itoa(i + 1);
		args->philo[i].var = args->var;
		args->philo[i].channel = &args->channel;
		args->philo[i].quit = &args->var.nb;
		args->philo[i].fork_left = &args->forks[i];
		args->philo[i].fork_right =
		&args->forks[(i - 1 + args->var.nb) % args->var.nb];
	}
	return (0);
}
