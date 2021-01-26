#include "philo_one.h"

int clear(t_args *args, int to_free)
{
	if (!to_free)
		free(args->forks);
	free(args);
	return (0);
}

unsigned long get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void update_last(t_philo *philo, unsigned long time_sleep)
{
	philo->last_time += time_sleep;
}

int sleep_philo(t_philo *philo, unsigned long time_sleep)
{
	usleep((philo->last_time + time_sleep - get_time_since_start(philo->var)) * 1000);
	update_last(philo, time_sleep);
	return (0);
}

/*
*** Affiche l'action via un seul write, pour limiter les appels sytèmes (syscalls)
*/

void display_action(t_philo *philo, char *action)
{
	char *to_print;
	char buffer[SIZE_BUFF];
	int i;

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
	pthread_mutex_lock(philo->channel);
	write(1, buffer, i);
	pthread_mutex_unlock(philo->channel);
}