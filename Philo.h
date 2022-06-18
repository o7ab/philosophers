/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabushar <oabushar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:26:25 by oabushar          #+#    #+#             */
/*   Updated: 2022/06/15 16:54:39 by oabushar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "limits.h"

typedef struct s_data{
    unsigned int n_philo;
    unsigned int td;
    unsigned int te;
    unsigned int ts;
    unsigned int n_eat;
}   t_data;

#endif