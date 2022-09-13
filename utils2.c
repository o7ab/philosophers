/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 02:16:30 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/14 03:15:10 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	go_sleep(t_philo *ph)
{
	ft_print('s', ph);
	my_sleep(ph, ph->info->ts);

}

void	ft_print(char c, t_philo *ph)
{
	// int long long	cur = (get_time() - ph->info->time);
	pthread_mutex_lock(&ph->info->mutex_print);
	if (c == 'f')
	{
		printf("%s[%lld] Philosopher %d has taken a fork\n", BYELLOW, get_time() - ph->info->time, ph->philo_id + 1);
		printf("%s[%lld] Philosopher %d has taken a fork\n", BYELLOW, get_time() - ph->info->time, ph->philo_id + 1);
		// return ;
	}
	else if (c == 'e')
	{
		printf("%s[%lld] Philosopher %d is eating\n", CYAN, get_time() - ph->info->time, ph->philo_id + 1);
		// ph->info->time += ph->info->te;
		// my_sleep(ph->info, ph->info->te);
		// return ;
	}
	else if (c == 's')
	{
		printf("%s[%lld] Philosopher %d is sleeping\n", BLUE, get_time() - ph->info->time, ph->philo_id + 1);
		// ph->info->time += ph->info->ts;
		// my_sleep(ph->info, ph->info->ts);
		// return ;
	}
	else if (c == 't')
	{
		printf("%s[%lld] Philosopher %d is thinking\n", PURPLE, get_time() - ph->info->time, ph->philo_id + 1);
		// return ;
	}
	pthread_mutex_unlock(&ph->info->mutex_print);
}