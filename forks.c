/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 11:51:31 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/24 02:28:09 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	set_fork(t_data *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_philo)
	{
		info->philo[i].philo_id = i;
		info->forks[i++] = 0;
	}
	i = 0;
	while (i < info->n_philo)
	{
		info->philo[i].left_fork = info->philo[i].philo_id;
		info->philo[i].right_fork = (i + 1) % info->n_philo;
		i++;
	}
}

void	drop_forks_odd(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
	ph->info->forks[ph->left_fork] = 0;
	ph->info->forks[ph->right_fork] = 0;
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
}

void	drop_forks(t_philo *ph)
{
	if (!ph->philo_id % 2)
	{
		drop_forks_odd(ph);
		return ;
	}
	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
	pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
	ph->info->forks[ph->right_fork] = 0;
	ph->info->forks[ph->left_fork] = 0;
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
}

int	check_forks_odd(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
	if (ph->info->forks[ph->right_fork])
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
	if (ph->info->forks[ph->right_fork])
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
		return (0);
	}
	ph->info->forks[ph->right_fork] = 1;
	ph->info->forks[ph->left_fork] = 1;
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
	return (1);
}

int	check_forks(t_philo *ph)
{
	if (!ph->philo_id % 2)
	{
		return (check_forks_odd(ph));
	}
	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
	if (ph->info->forks[ph->left_fork])
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
	if (ph->info->forks[ph->right_fork])
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
		return (0);
	}
	ph->info->forks[ph->left_fork] = 1;
	ph->info->forks[ph->right_fork] = 1;
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
	return (1);
}
