/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschwere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 13:55:06 by aschwere          #+#    #+#             */
/*   Updated: 2019/10/16 07:59:55 by aschwere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

unsigned long			get_time_since_start(t_var var)
{
	return (get_time() - var.start);
}

int						order(long int n)
{
	int res;

	res = 1;
	while (n > 9)
	{
		n = n / 10;
		res += 1;
	}
	return (res);
}

char					*ft_write(char *res, long int n, int size)
{
	int debut;

	if (res[0] == '-')
		debut = 1;
	else
		debut = 0;
	res[size] = '\0';
	size -= 1;
	while (size >= debut)
	{
		res[size] = n % 10 + '0';
		n = n / 10;
		size--;
	}
	return (res);
}

size_t					ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int						ft_atoi(const char *str)
{
	int res;
	int i;
	int signe;

	i = 0;
	res = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
	str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i += 1;
	else if (str[i] == '-')
	{
		i += 1;
		signe *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = 10 * res + (str[i] - '0');
		i++;
	}
	return (res * signe);
}
