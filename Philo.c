/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/10 13:09:36 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

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
		//my_sleep(ph->info, ph->info->te);
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
		printf("%s[%lld] Philosopher %d is thinking\n", PURPLE, get_time() - ph->info->time ,ph->philo_id + 1);
		// return ;
	}
	pthread_mutex_unlock(&ph->info->mutex_print);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex_all_eat);
	ft_print('f', philo);
	// if (philo->times_ate > philo->info->n_eat)
	// 	return ;
	// pthread_mutex_lock(&philo->info->mutex_print);
	ft_print('e', philo);
	// pthread_mutex_unlock(&philo->info->mutex_all_eat);
	//pthread_mutex_lock(&philo->info->mutex_all_eat);
	my_sleep(philo->info, philo->info->te);
	//philo->times_ate++;
	// if (philo->times_ate == philo->info->n_eat)
	// 	philo->info->all_eat++;
	pthread_mutex_unlock(&philo->info->mutex_all_eat);
}

void	go_sleep(t_philo *ph)
{
	ft_print('s', ph);
	my_sleep(ph->info, ph->info->ts);

}

// void	test_forks(t_philo *ph)
// {
// 	pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
// 	pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
// 	if (!ph->info->forks[ph->left_fork] && !ph->info->forks[ph->right_fork])
// 	{
// 		ph->info->forks[ph->left_fork] = 1;
// 		ph->info->forks[ph->right_fork] = 1;
// 		eating(ph);
// 		// pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
// 		// pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
// 		// return ;
// 	}
// 	pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
// 	pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
// }

void	*ft_thread(void *info)
{
	// int time = 0;
	t_philo *ph = (t_philo *)info;
	// (void) data;
	// if (ph->philo_id % 2) 5000);
	while (1)
	{
		if (check_forks_even(ph))
		{
		
			go_sleep(ph);
			ft_print('t', ph);
		}    
		// printf("AY IT DID START\n");
		// eating(ph);
		// go_sleep(ph);
		//usleep500;
		//printf("ph: %d meals: %d\n", ph->philo_id, ph->times_ate);
		// if (ph->info->all_eat == ph->info->n_philo)
		// 	break;
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