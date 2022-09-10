/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/10 11:22:39 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_atoi(const char *str)
{
	size_t	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = (num * 10) + (str[i] - '0');
		if (num > INT_MAX)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	return (sign * num);
}

int check_arg(char **argv, t_data *data)
{
	int i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	i = 0;
	data->n_philo = ft_atoi(argv[1]);
	data->td = ft_atoi(argv[2]);
	data->te = ft_atoi(argv[3]);
	data->ts = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->n_eat = ft_atoi(argv[5]);
		if (data->n_eat <= 0)
			return (0);
	}
	if (data->n_philo <= 0 || data->td <= 60 || data->ts <= 60 || data->te <= 60)
		return (0);
	data->dead = 0;
	data->all_eat = 0;
	return (1);
}

int	ft_init_mutex(t_data *info)
{
	unsigned int i;

	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&info->mutex_forks[i++], NULL))
			return (0);
	}
	if (pthread_mutex_init(&info->mutex_print, NULL))
		return (0);
	if (pthread_mutex_init(&info->mutex_all_eat, NULL))
		return (0);
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while ((s1[i] || s2[i]) && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int long long	get_time()
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(t_data *info, int ms)
{
	long long	t;

	(void) info;
	t = get_time();
	while (get_time() - t < ms)
		usleep(100);
}

void	ft_print(char c, t_philo *ph)
{
	pthread_mutex_lock(&ph->info->mutex_print);
	// int long long	cur = (get_time() - ph->info->time);
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
	my_sleep(philo->info, philo->info->te);
	pthread_mutex_unlock(&philo->info->mutex_all_eat);
	//pthread_mutex_lock(&philo->info->mutex_all_eat);
	//philo->times_ate++;
	// if (philo->times_ate == philo->info->n_eat)
	// 	philo->info->all_eat++;
	//pthread_mutex_unlock(&philo->info->mutex_all_eat);
}

void	drop_forks_even(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]))
		return ;
	if (ph->info->forks[ph->right_fork] != ph->philo_id)
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
		return ;
	}
	else
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
		pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]);
		if (ph->info->forks[ph->left_fork] != ph->philo_id)
		{
			pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
			return ;
		}
		ph->info->forks[ph->right_fork] = -1;
		ph->info->forks[ph->left_fork] = -1;
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
	}
}

void	go_sleep(t_philo *ph)
{
	ft_print('s', ph);
	my_sleep(ph->info, ph->info->ts);

}

int	check_forks_even(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->info->mutex_forks[ph->left_fork]))
		return (0);
	// printf("even- Philo id is %d\n", ph->philo_id + 1);
	if (ph->info->forks[ph->left_fork] == ph->philo_id)
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->left_fork]);
		pthread_mutex_lock(&ph->info->mutex_forks[ph->right_fork]);
		// printf("2 - Philo id is %d:\tleft:%d\tright:%d\n",ph->philo_id, ph->info->forks[ph->left_fork], ph->info->forks[ph->right_fork]);
		if (ph->info->forks[ph->right_fork] == ph->philo_id)
		{
			// printf("----------- \n");
			pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
			return (0);
		}
		ph->info->forks[ph->right_fork] = ph->philo_id;
		ph->info->forks[ph->left_fork] = ph->philo_id;
		// printf("test shiiiiiiiiii\n");
		pthread_mutex_unlock(&ph->info->mutex_forks[ph->right_fork]);
		// drop_forks_even(ph);
	}
	return (1);
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
			eating(ph);
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

void	set_fork(t_data *info)
{
	unsigned int i = 0;
	
	while (i < info->n_philo)
	{
		info->philo[i].philo_id = i;
		info->forks[i++] = -1;
	}
	i = 0;
	while (i < info->n_philo)
	{
		info->philo[i].left_fork = info->philo[i].philo_id;
		if (info->philo[i].philo_id == (int)info->n_philo - 1)
			info->philo[i].right_fork = 0;
		else
			info->philo[i].right_fork = info->philo[i].philo_id + 1;
		i++;
	}
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