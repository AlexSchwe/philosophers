/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 20:16:50 by aschwere          #+#    #+#             */
/*   Updated: 2020/11/16 18:35:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (((s1[i]) == s2[i]) && (s1[i] || s2[i]))
	{
		i++;
	}
	return ((unsigned)(s1[i]) - (unsigned)(s2[i]));
}

char			*ft_itoa(int nb)
{
	char		*res;
	int			size;
	int long	n;

	n = nb;
	if (n < 0)
	{
		n *= -1;
		if (!(res = malloc((order(n) + 2) * sizeof(char))))
			return (NULL);
		res[0] = '-';
		size = order(n) + 1;
	}
	else
	{
		size = order(n);
		if (!(res = malloc((order(n) + 1) * sizeof(char))))
			return (NULL);
	}
	res = ft_write(res, n, size);
	return (res);
}

unsigned long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void			update_last(t_philo *philo, unsigned long time_sleep)
{
	philo->last_time += time_sleep;
}

int				sleep_philo(t_philo *philo, unsigned long time_sleep)
{
	usleep((philo->last_time + time_sleep
	- get_time_since_start(philo->var)) * 1000);
	update_last(philo, time_sleep);
	return (0);
}
