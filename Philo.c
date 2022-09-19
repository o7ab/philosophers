/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/19 20:23:37 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	eating(t_philo *philo)
{
	ft_print('f', philo);
	ft_print('e', philo);
	philo->last_meal = get_time();
	my_sleep(philo, philo->info->te);
	philo->times_ate++;
}

int	test_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
	pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
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
	// usleep(100);
	// ft_print('k', ph);
	return (0);
}

void	one_down(t_philo *ph)
{
	printf("%s[%d] Philosopher %d has taken a fork\n", BYELLOW, 0, ph->philo_id + 1);
	printf("%s[%u] Philosopher %d has died\n", WHITE, ph->info->td, ph->philo_id + 1);
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

// int	death_monitor(t_philo *ph)
// {
// 	pthread_mutex_lock(&ph->info->mutex_dead);
// 	if (get_time() - ph->last_meal >= ph->info->td)
// 	{
// 		ft_print('d', ph);
// 		*ph->death_flag = 1;
// 		pthread_mutex_unlock(&ph->info->mutex_dead);
// 		return (0);
// 	}
// 	printf("death_monitor %d\n", *ph->death_flag);
// 	pthread_mutex_unlock(&ph->info->mutex_dead);
// 	return (1);
// }

void	*ft_thread(void *info)
{
	t_philo *ph = (t_philo *)info;

	ph->last_meal = get_time();
	while (!*ph->death_flag && ph->times_ate < ph->info->n_eat)
	{
		if (check_forks(ph))
		{
			eating(ph);
			drop_forks(ph);
			go_sleep(ph);
			ft_print('t', ph);
		}
	}
	return (NULL);
}



void	 ft_init_philo(t_data *info)
{
	unsigned int	i;

	i = 0;
	info->dead = malloc(sizeof(int));
	info->time = get_time();
	while (i < info->n_philo)
	{
		info->philo[i].info = info;
		info->philo[i].death_flag = info->dead;
		// info->philo[i].last_meal = get_time();
		info->philo[i].times_ate = 0;
		// info->philo[i].philo_id = i;
		i++;
	}
	i = 0;
	if (info->n_philo == 1)
	{
		one_down(&info->philo[0]);
		return ;
	}
	while (i < info->n_philo)
	{
		pthread_create(&info->phils[i], NULL, &ft_thread, &info->philo[i]);
		usleep(100);
		i++;
	}
	i = 0;
	// while (i < info->n_philo)
	// {
	// 	if (i >= info->n_philo)
	// 		i = 0;
	// 	if (!death_monitor(&info->philo[i]))
	// 		break;;
	// 	i++;
	// }
	// i = 0;
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
	free (info.dead);
	return (0);
}