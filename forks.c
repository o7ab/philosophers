/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 11:51:31 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/13 14:18:44 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	set_fork(t_data *info)
{
	unsigned int i = 0;
	
	while (i < info->n_philo)
	{
		info->philo[i].philo_id = i;
		info->forks[i++] = 0;
	}
	i = 0;
	while (i < info->n_philo)
	{
		info->philo[i].left_fork = info->philo[i].philo_id;
		// if (info->philo[i].philo_id == (int)info->n_philo - 1)
		// 	info->philo[i].right_fork = 0;
		info->philo[i].right_fork = (i + 1) % info->n_philo;
		i++;
	}
	
}

// void	drop_forks_even(t_philo *ph)
// {
// 	if (pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]))
// 		return ;
// 	if (!ph->info->forks[ph->right_fork])
// 	{
// 		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
// 		return ;
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
// 		pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
// 		if (ph->info->forks[ph->left_fork])
// 		{
// 			pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
// 			return ;
// 		}
// 		ph->info->forks[ph->right_fork] = 0;
// 		ph->info->forks[ph->left_fork] = 0;
// 		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
// 	}
// }
void	drop_forks_even(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
	pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
	// printf("philo id %d left %d right %d\n", ph->philo_id, ph->info->forks[ph->left_fork], ph->info->forks[ph->right_fork]);
	if (ph->info->forks[ph->right_fork] > 0 && ph->info->forks[ph->left_fork] > 0)
	{
		ph->info->forks[ph->right_fork] = 0;
		ph->info->forks[ph->left_fork] = 0;
	}
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
}

int	check_forks_even(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
	if (ph->info->forks[ph->left_fork])
	{
		// printf("even- Philo id is %d\n", ph->philo_id + 1);
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
		pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
		if (ph->info->forks[ph->right_fork])
		{
			// printf("----------- \n");
			pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
			return (0);
		}
		// printf("test shiiiiiiiiii\n");
		ph->info->forks[ph->left_fork] = 1;
		ph->info->forks[ph->right_fork] = 1;
		// eating(ph);
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
		// printf("the philo_id is %d\t The left fork is %d\t the right fork is %d\n", ph->philo_id + 1, ph->info->forks[ph->left_fork], ph->info->forks[ph->right_fork]);
		// drop_forks_even(ph);
	}
	return (1);
}