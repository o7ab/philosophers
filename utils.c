/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 11:55:19 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/19 20:16:35 by oabushar         ###   ########.fr       */
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

int check_arg(char **argv, t_data *data)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	i = 0;
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
	if (data->n_philo <= 0 || data->td <= 60 || data->ts <= 60 || data->te <= 60)
		return (0);
	data->dead = 0;
	data->all_eat = 0;
	// data_
	return (1);
}

int	ft_init_mutex(t_data *info)
{
	unsigned int i;

	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&info->mutex_forks[i++], NULL))
			return (0);
	}
	if (pthread_mutex_init(&info->mutex_print, NULL))
		return (0);
	if (pthread_mutex_init(&info->mutex_all_eat, NULL))
		return (0);
	if (pthread_mutex_init(&info->mutex_dead, NULL))
		return (0);
	return (1);
}

int long long	get_time()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(t_philo *ph, int ms)
{
	long long	t;

	(void) ph;
	t = get_time();
	// pthread_mutex_lock(&ph->info->mutex_dead);
	while (get_time() - t < ms)
	{
		// if (get_time() - ph->last_meal >= ph->info->td)
		// 	break ;
		usleep(ms);
	}
}