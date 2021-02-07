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

#include "philo_three.h"

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

int				ft_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (((s1[i]) == s2[i]) && (s1[i] || s2[i]))
	{
		i++;
	}
	return ((unsigned)(s1[i]) - (unsigned)(s2[i]));
}

unsigned long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int				sleep_philo(unsigned long time_sleep)
{
	usleep(time_sleep * 1000);
	return (0);
}
