/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/14 03:36:42 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	eating(t_philo *philo)
{
	// printf("philo id is %d\n", philo->philo_id);
	if (philo->times_ate > philo->info->n_eat)
		return ;
	ft_print('f', philo);
	// pthread_mutex_lock(&philo->info->mutex_print);
	ft_print('e', philo);
	philo->last_meal = 0;
	// pthread_mutex_unlock(&philo->info->mutex_all_eat);
	//pthread_mutex_lock(&philo->info->mutex_all_eat);
	my_sleep(philo, philo->info->te);
	// if (philo->death_flag)
	// {
	// 	ft_print('d', philo);
	// 	return ;
	// }
	pthread_mutex_lock(&philo->info->mutex_all_eat);
	philo->times_ate++;
	if (philo->times_ate == philo->info->n_eat)
		philo->info->all_eat++;
	pthread_mutex_unlock(&philo->info->mutex_all_eat);
}

int	test_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
	pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
	// if (ph->philo_id % 2) 
	// 	usleep(5000);
	if (ph->info->forks[ph->left_fork] == 0 && ph->info->forks[ph->right_fork] == 0)
	{
		ph->info->forks[ph->left_fork] = 1;
		ph->info->forks[ph->right_fork] = 1;
		// eating(ph);
		// printf("  testing philo id %d left %d right %d\n", ph->philo_id, ph->info->forks[ph->left_fork], ph->info->forks[ph->right_fork]);
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
		return (1);
	}
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
	return (0);
}

void	*ft_thread(void *info)
{
	// int time = 0;
	t_philo *ph = (t_philo *)info;
	// (void) data;
	// if (ph->philo_id % 2) 
	// 	usleep(50);
	// printf("lf: %d, rf: %d\n", ph->left_fork, ph->right_fork);
	ph->last_meal = get_time();
	while (!ph->death_flag)
	{
		if (check_forks_even(ph))
		{
			eating(ph);
			drop_forks_even(ph);
			go_sleep(ph);
			ft_print('t', ph);
		}    
		usleep(100);
		// printf("AY IT DID START\n");
		// printf("ph: %d meals: %d\n", ph->philo_id, ph->times_ate);
		if (ph->info->all_eat == ph->info->n_philo)
			break;
	}
	return (NULL);
}

void	 ft_init_philo(t_data *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_philo)
	{
		info->philo[i].info = info;
		info->philo[i].times_ate = 0;
		// info->philo[i].philo_id = i;
		i++;
	}
	i = 0;
	info->time = get_time();
	while (i < info->n_philo)
	{
		pthread_create(&info->phils[i], NULL, &ft_thread, &info->philo[i]);
		i++;
		// usleep(100);
	}
	i = 0;
	while (i < info->n_philo)
		pthread_join(info->phils[i++], NULL);
}

int main(int argc, char **argv)
{
	// pthread_t		thread;
	// struct timeval time;
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
	set_fork(&info);
	if (!ft_init_mutex(&info))
		return (0);
	ft_init_philo(&info);
	return (0);
}