/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/08/25 03:52:59 by oabushar         ###   ########.fr       */
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

void	*ft_test()
{
	printf("test\n");
	int i = 0;
	i++;
	printf("Test\n");
	return (NULL);
}

void	ft_init_mutex(t_data *info)
{
	unsigned int i;
	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_mutex_init(&info->mutex[i++], NULL))
			return ;
	}
}

// void	ft_even(t_data *info)
// {
// 	while (1) 
// 	{
// 		if ()
// 		printf("Philosopher");
		
// 	}
// }

void	ft_print(char *str, t_data *info)
{
	if ()
}

void	*ft_thread(void *info)
{
	int time = 0;
	int j = 0;
	
	t_data *data = (t_data *)info;
	while (1)
	{
		if (data->philo[j].l_r = 1)
		{
			printf("[%d] Philosopher %d is eating\n", data->te * time, data->philo[j].l_r);
			usleep(data->te);
			data->philo[j].l_r = 0;
		}
	}
	// if (data->n_philo % 2 == 0)
	// {
	// 	ft_even(data);
	// }
	// else if (data->n_philo % 2 == 1)
	// {
	// 	(void) data;
	// }

	return (NULL);
}

void	ft_init_philo(t_data *info)
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
	ft_init_mutex(&info);
	ft_init_philo(&info);
	return (0);
}