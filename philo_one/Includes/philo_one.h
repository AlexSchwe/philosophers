/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/07 02:38:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# define NB_PHILO_ERROR "At least two philosophers, please\n"
# define TIME_ERROR "Time to die must be a strictly positive number !\n"
# define EAT_ERROR "Time to eat must be a strictly positive number !\n"
# define SLEEP_ERROR "Time to sleep must be a strictly positive number !\n"
# define ROUND_ERROR "Number of rounds must be a strictly positive number !\n"
# define NB_ARGS "Please give me 4 or 5 arguments\n"
# define EAT "is eating\n"
# define FORK "has taken a fork\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DEATH "suddenly died, may his soul rest in peace\n"
# define SIZE_BUFF 128
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>
# include <errno.h>
# include <stdio.h>

typedef struct			s_var
{
	int					nb;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					round;
	unsigned long		start;
}						t_var;

typedef struct			s_philo
{
	t_var				var;
	unsigned long		last_time;
	unsigned long		death;
	int					*quit;
	char				*name;
	pthread_t			action;
	pthread_t			control;
	pthread_mutex_t		death_time;
	pthread_mutex_t		state;
	pthread_mutex_t		*channel;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
}						t_philo;

typedef struct			s_args
{
	t_var				var;
	pthread_mutex_t		*forks;
	pthread_mutex_t		channel;
	t_philo				*philo;
}						t_args;

unsigned long			get_time_since_start(t_var var);

void					*philo_control(void *arg);

void					handle_eat(t_philo *philo);

void					*philo_life(void *arg);

void					wait_for_all_threads(t_args *args);

int						order(long int n);

void					update_last(t_philo *philo, unsigned long time_sleep);

char					*ft_write(char *res, long int n, int size);

char					*ft_itoa(int nb);

void					display_action(t_philo *philo, char *action);

size_t					ft_strlen(const char *s);

int						ft_atoi(const char *str);

int						check_arg(int argc, char **argv, t_args *args);

int						sleep_philo(t_philo *philo, unsigned long time_sleep);

int						check_death(unsigned long time_death);

void					start_mutexes(t_args *args);

void					create_thread(t_args *args, int i);

void					start_threads(t_args *args);

int						clear(t_args *args, int to_free);

int						set_philosophers(t_args *args);

unsigned long			get_time(void);

#endif
