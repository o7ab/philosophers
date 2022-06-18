/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:25:53 by oabushar          #+#    #+#             */
/*   Updated: 2022/06/15 17:15:10 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void    ft_exit()
{
	printf("Invalid arguements\n");
	exit(1);
}

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
			ft_exit();
		i++;
	}
	if (str[i])
		ft_exit();
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
		data->n_eat = ft_atoi(argv[5]);
	return (1);
}

int main(int argc, char **argv)
{
	t_data data;
	if (!(argc == 5 || argc == 6))
	{
		printf("Invalid number of arguements\n");
		return (0);
	}
	if (!check_arg(argv, &data))
		printf("Invalid arguements\n");
}