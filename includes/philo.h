/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:46:54 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/09 11:59:25 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_global
{
	long	p_nb;
	long	t_td;
	long	t_te;
	long	t_ts;
	long	n_eat;
	t_philo	*philo;
}			t_global;

typedef struct s_data
{
	int			id;
	int			n_eat;
}			t_data;

typedef struct s_philo
{
	t_data		data;
	pthread_t	thread;
}			t_philo;

//#######################################################//
//# 						INIT 						#//
//#######################################################//

long		ft_atol(char *str);
t_global	*get_global(char **argv);

//#######################################################//
//# 					   PARSING						#//
//#######################################################//

int		ft_isdigit(char *str);
int		check_args(char **argv);

//#######################################################//
//# 					   ROUTINE						#//
//#######################################################//

void		*routine();

//#######################################################//
//# 						UTILS						#//
//#######################################################//

#endif