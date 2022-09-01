/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:26:25 by oabushar          #+#    #+#             */
/*   Updated: 2022/09/01 05:04:49 by oabushar         ###   ########.fr       */
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

typedef struct s_philo{
	int death_flag;
	int philo_id;
	int last_meal;
	int	left_fork;
	int	right_fork;
	struct s_data info;

}	t_philo;

typedef struct s_data{
	t_philo			philo[200];
    unsigned int	n_philo;
    unsigned int	td;
    unsigned int	te;
    unsigned int	ts;
    unsigned int	n_eat;
	int				time;
	int				*forks;
	pthread_t		phils[200];
	pthread_mutex_t mutex[200];
}   t_data;

#endif