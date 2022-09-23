/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/23 02:39:39 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	eating(t_philo *philo)
{
	philo->last_meal = get_time();
	ft_print('f', philo);
	ft_print('e', philo);
	my_sleep(philo, philo->info->te);
	philo->times_ate++;
	pthread_mutex_lock(&philo->info->mutex_eat);
	if (philo->times_ate >= philo->info->n_eat)
		philo->info->all_eat = 1;
	pthread_mutex_unlock(&philo->info->mutex_eat);
}

int	death_check(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->mutex_dead); 
	if (get_time() - ph->last_meal >= ph->info->td)
	{
		print_death(ph);
		*ph->death_flag = 1;
		pthread_mutex_unlock(&ph->info->mutex_dead);
		return (0);
	}
	pthread_mutex_unlock(&ph->info->mutex_dead);
	return (1);
}

void	*ft_thread(void *info)
{
	t_philo	*ph;

	ph = (t_philo *)info;
	ph->last_meal = get_time();
	if (ph->philo_id % 2)
		usleep(100);
	while (!*ph->death_flag && ph->times_ate < ph->info->n_eat)
	{
		while (!check_forks(ph))
			usleep(50);
		eating(ph);
		drop_forks(ph);
		go_sleep(ph);
		ft_print('t', ph);
		usleep(500);
	}
	return (NULL);
}

int	death_monitor(t_data *info)
{
	unsigned int	i;

	i = 0;
	while (!*info->dead && !info->all_eat)
	{
		i = 0;
		while (i < info->n_philo)
		{
			if (!death_check(&info->philo[i]))
				break ;
			i++;
		}
		usleep(100);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	info;

	if (!(argc == 5 || argc == 6))
	{
		printf("Invalid number of arguements\n");
		return (0);
	}
	if (!check_arg(argv, &info))
	{
		printf("Invalid arguements\n");
		return (0);
	}
	if (info.n_philo == 1)
	{
		one_down(&info.philo[0]);
		return (0);
	}
	set_fork(&info);
	if (!ft_init_mutex(&info))
		return (0);
	ft_init_philo(&info);
	destroy_mutex(&info);
	return (0);
}
