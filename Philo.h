/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:26:25 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/10 10:27:27 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "limits.h"
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

# define CYAN "\e[1;96m"
# define PURPLE "\e[1;95m"
# define BLUE "\033[1;34m"
# define BYELLOW  "\033[1;33m"

typedef struct s_philo{
	int death_flag;
	int philo_id;
	int last_meal;
	int	left_fork;
	int	right_fork;
	unsigned int times_ate;
	pthread_mutex_t left_mutex;
	pthread_mutex_t right_mutex;
	struct s_data *info;
}	t_philo;

typedef struct s_data{
	struct s_philo	philo[200];
    unsigned int	n_philo;
    unsigned int	td;
    unsigned int	te;
    unsigned int	ts;
    unsigned int	n_eat;
	int	long long	time;
	unsigned int	all_eat;
	unsigned int	dead;
	int				forks[250];
	pthread_t		phils[200];
	pthread_mutex_t mutex_forks[200];
	pthread_mutex_t mutex_print;
	pthread_mutex_t mutex_all_eat;
	pthread_mutex_t mutex_dead;
	
}   t_data;

#endif