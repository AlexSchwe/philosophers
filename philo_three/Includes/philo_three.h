/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 19:50:07 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/07 02:38:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
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
# include <semaphore.h>
# include <stddef.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>

typedef struct			s_var
{
	int					nb;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					round;
	unsigned long		start;
	sem_t				*channel;
	sem_t				*forks;
	sem_t				*alive;
	sem_t				*prio;
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
	sem_t				*state;
}						t_philo;

typedef struct			s_args
{
	t_var				var;
	t_philo				*philo;
	pid_t				*pids;
}						t_args;

unsigned long			get_time_since_start(t_var var);

void					*philo_control(void *arg);

void					handle_eat(t_philo *philo);

void					*philo_life(void *arg);

void					wait_for_all_threads(t_args *args);

int						order(long int n);

char					*ft_write(char *res, long int n, int size);

char					*ft_itoa(int nb);

void					display_action(t_philo *philo, char *action);

size_t					ft_strlen(const char *s);

int						ft_atoi(const char *str);

int						check_arg(int argc, char **argv, t_args *args);

int						sleep_philo(unsigned long time_sleep);

int						check_death(unsigned long time_death);

void					start_sem(t_args *args);

void					create_thread(t_args *args, int i);

void					start_processes(t_args *args);

int						set_philosophers(t_args *args);

unsigned long			get_time(void);

void					handle_eat(t_philo *philo);

void					handle_fork(t_philo *philo);

void					handle_sleep(t_philo *philo);

void					destroy_semaphores(t_args *args);

char					*semaphore_name(char *number);

sem_t					*open_new_semaphore(char *name, int value);

int						clear(t_args *args, char *str);

void					start_semaphores(t_args *args);

int						ft_strcmp(char *s1, char *s2);

void					start_monitoring(t_args *args);
#endif
