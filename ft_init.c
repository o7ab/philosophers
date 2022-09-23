/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:49:05 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/23 02:13:09 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

static void	start_philo(t_data *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_create(&info->phils[i], NULL, &ft_thread, &info->philo[i]);
		usleep(100);
		i++;
	}
	i = 0;
	death_monitor(info);
	if (info->dead)
		pthread_mutex_unlock(&info->mutex_dead);
	while (i < info->n_philo)
		pthread_join(info->phils[i++], NULL);
}

void	destroy_mutex(t_data *info)
{
	unsigned int	i;

	i = 0;
	free (info->dead);
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->mutex_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->mutex_print);
	pthread_mutex_destroy(&info->mutex_dead);
}

void	ft_init_philo(t_data *info)
{
	unsigned int	i;

	i = 0;
	info->dead = malloc(sizeof(int));
	if (!info->dead)
		return ;
	*info->dead = 0;
	info->time = get_time();
	info->all_eat = 0;
	while (i < info->n_philo)
	{
		info->philo[i].info = info;
		info->philo[i].death_flag = info->dead;
		info->philo[i].times_ate = 0;
		i++;
	}
	start_philo(info);
}
