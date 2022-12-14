/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 11:55:19 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/26 15:19:17 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_atoi(const char *str)
{
	size_t	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = (num * 10) + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	return (sign * num);
}

int	check_arg(char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	data->n_philo = ft_atoi(argv[1]);
	data->td = ft_atoi(argv[2]);
	data->te = ft_atoi(argv[3]);
	data->ts = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->n_eat = ft_atoi(argv[5]);
		if (data->n_eat <= 0)
			return (0);
	}
	else if (!argv[5])
		data->n_eat = 99999999;
	if (data->n_philo <= 0 || data->td <= 60 || data->ts <= 60
		|| data->te <= 60 || data->n_philo > 200)
		return (0);
	return (1);
}

int	ft_init_mutex(t_data *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&info->mutex_forks[i++], NULL))
			return (0);
	}
	if (pthread_mutex_init(&info->mutex_print, NULL))
		return (0);
	if (pthread_mutex_init(&info->mutex_dead, NULL))
		return (0);
	if (pthread_mutex_init(&info->mutex_eat, NULL))
		return (0);
	if (pthread_mutex_init(&info->var_2, NULL))
		return (0);
	return (1);
}

int long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(t_philo *ph, int ms)
{
	long long	t;

	t = get_time();
	while (get_time() - t < ms)
	{
		if (get_time() - ph->last_meal >= ph->info->td)
			break ;
		usleep(ms);
	}
}
