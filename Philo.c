/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/01 05:28:18 by oabushar         ###   ########.fr       */
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
	return (1);
}

void	ft_init_mutex(t_data *info)
{
	unsigned int i;

	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&info->mutex[i], NULL))
			return ;
	}
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

void	ft_print(char *str, t_data *data)
{
	if (!(ft_strcmp(str, "fork")))
	{
		printf("[%d] Philosopher %d has taken a fork\n", data->time, data->philo[data->philo->philo_id].philo_id);
	}
	if (!(ft_strcmp(str, "eat")))
	{
		printf("[%d] Philosopher %d is eating\n", data->time, data->philo[data->philo->philo_id].philo_id);
		usleep (data->te);
	}
	if (!ft_strcmp(str, "sleep"))
	{
		printf("[%d] Philosopher %d is sleeping\n", data->time, data->philo[data->philo->philo_id].philo_id);
		usleep(data->ts);
	}
	if (!ft_strcmp(str, "thinking"))
	{
		printf("[%d] Philosopher %d is sleeping\n", data->time, data->philo[data->philo->philo_id].philo_id);
	}
}

int	check_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->info.mutex[ph->left_fork]);
	if (ph->info.forks[ph->left_fork] != ph->philo_id)
	{
		if (ph->info.forks[ph->philo_id] && ph->philo_id != ph->info.n_philo)
		{
			ph->info.forks[ph->philo_id] = 0;
			ph->info.forks[ph->philo_id - 1] = 0;
			ft_print("fork", &ph->info);
		}
		else if (ph->info.forks[0] && ph->philo_id == ph->info.n_philo)
		{
			ph->info.forks[0] = 0;
			ph->info.forks[ph->philo_id - 1] = 0;
			ft_print("fork", &ph->info);
		}
		else
			return(0);
	}
	pthread_mutex_unlock(&ph->info.mutex[ph->left_fork]);
	return (1);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->info.mutex[philo->philo_id]);
	ft_print("eat", philo->info);
	pthread_mutex_unlock(&philo->info.mutex[philo->philo_id]);
}

void	*ft_thread(void *info)
{
	// int time = 0;
	int j = 0;
	
	t_data *data = (t_data *)info;
	while (j < data->n_philo)
	{
		if (check_forks(&data->philo[j]) == 0)
			j++;
		else
			eating(&data->philo[j]);
	}
	return (NULL);
}

void	 ft_init_philo(t_data *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_philo)
	{
		info->philo->philo_id = i + 1;
		pthread_create(&info->phils[i++], NULL, &ft_thread, (void *)info);
	}
	i = 0;
	while (i < info->n_philo)
		pthread_join(info->phils[i++], NULL);
}

void	set_fork(t_data *info)
{
	unsigned int i = 0;
	
	while (i < info->n_philo)
		info->forks[i++] = -1;
	i = 0;
	while (i < info->n_philo)
	{
		if (info->philo[i].philo_id == info->n_philo)
			info->philo[i].right_fork = info->philo[0].philo_id;
		else
		{
			info->philo[i].left_fork = info->philo[i].philo_id;
			info->philo[i].right_fork = info->philo[i].philo_id + 1;
		}
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
	info.time = 0;
	info.forks = malloc(sizeof(int) * info.n_philo);
	set_fork(&info);
	ft_init_mutex(&info);
	ft_init_philo(&info);
	return (0);
}