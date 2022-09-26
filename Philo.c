/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/26 15:16:37 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	eating(t_philo *philo)
{
	ft_print('f', philo);
	ft_print('e', philo);
	pthread_mutex_lock(&philo->info->mutex_eat);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->info->mutex_eat);
	my_sleep(philo, philo->info->te);
	philo->times_ate++;
	pthread_mutex_lock(&philo->info->mutex_eat);
	if (philo->times_ate >= philo->info->n_eat)
		philo->info->all_eat = 1;
	pthread_mutex_unlock(&philo->info->mutex_eat);
}

int	death_check(t_philo *ph)
{
	long long	temp;

	pthread_mutex_lock(&ph->info->mutex_eat);
	temp = get_time() - ph->last_meal;
	pthread_mutex_unlock(&ph->info->mutex_eat);
	pthread_mutex_lock(&ph->info->mutex_dead);
	if (temp >= ph->info->td)
	{
		pthread_mutex_unlock(&ph->info->mutex_dead);
		print_death(ph);
		pthread_mutex_lock(&ph->info->var_2);
		*ph->death_flag = 1;
		pthread_mutex_unlock(&ph->info->var_2);
		return (0);
	}
	pthread_mutex_unlock(&ph->info->mutex_dead);
	return (1);
}

void	*ft_thread(void *info)
{
	t_philo	*ph;
	int		temp;

	ph = (t_philo *)info;
	thread_help(ph);
	pthread_mutex_lock(&ph->info->var_2);
	temp = *ph->death_flag;
	pthread_mutex_unlock(&ph->info->var_2);
	while (!temp && ph->times_ate < ph->info->n_eat)
	{
		while (!check_forks(ph))
			usleep(50);
		eating(ph);
		drop_forks(ph);
		go_sleep(ph);
		ft_print('t', ph);
		usleep(500);
		pthread_mutex_lock(&ph->info->var_2);
		temp = *ph->death_flag;
		pthread_mutex_unlock(&ph->info->var_2);
	}
	return (NULL);
}

int	death_monitor(t_data *info)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&info->mutex_eat);
	while (!*info->dead && !info->all_eat)
	{
		pthread_mutex_unlock(&info->mutex_eat);
		i = 0;
		while (i < info->n_philo)
		{
			if (!death_check(&info->philo[i]))
				break ;
			i++;
		}
		usleep(100);
		pthread_mutex_lock(&info->mutex_eat);
	}
	pthread_mutex_unlock(&info->mutex_eat);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*info;

	info = (t_data *)calloc(1, sizeof(t_data));
	if (!info)
		return (0);
	if (!(argc == 5 || argc == 6))
	{
		free(info);
		printf("Invalid number of arguements\n");
		return (0);
	}
	if (!check_arg(argv, info))
	{
		free(info);
		printf("Invalid arguements\n");
		return (0);
	}
	set_fork(info);
	if (!ft_init_mutex(info))
		return (0);
	ft_init_philo(info);
	destroy_mutex(info);
	return (0);
}
