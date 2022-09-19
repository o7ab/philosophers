/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 02:16:30 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/19 19:43:40 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	go_sleep(t_philo *ph)
{
	ft_print('s', ph);
	my_sleep(ph, ph->info->ts);
	// death_check(ph);
}

void	print_death(t_philo *ph)
{
	// pthread_mutex_lock(&ph->info->mutex_print);
	if (*ph->death_flag)
	{
		pthread_mutex_unlock(&ph->info->mutex_print);
		return ;
	}
	printf("%s[%lld] Philosopher %d has died\n", WHITE, get_time() - ph->info->time, ph->philo_id + 1);
	// pthread_mutex_unlock(&ph->info->mutex_print);
}

void	ft_print(char c, t_philo *ph)
{
	int long long	cur = (get_time() - ph->info->time);
	pthread_mutex_lock(&ph->info->mutex_print);
	if (c == 'f')
	{
		printf("%s[%lld] Philosopher %d has taken a fork\n", BYELLOW, cur, ph->philo_id + 1);
		printf("%s[%lld] Philosopher %d has taken a fork\n", BYELLOW, cur, ph->philo_id + 1);
	}
	else if (c == 'e')
		printf("%s[%lld] Philosopher %d is eating\n", CYAN, cur, ph->philo_id + 1);
	else if (c == 's')
		printf("%s[%lld] Philosopher %d is sleeping\n", BLUE, cur, ph->philo_id + 1);
	else if (c == 't')
		printf("%s[%lld] Philosopher %d is thinking\n", PURPLE, cur, ph->philo_id + 1);
	else if (c == 'k')
		printf("TEST \n");
	pthread_mutex_unlock(&ph->info->mutex_print);
}