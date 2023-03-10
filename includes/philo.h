/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:46:54 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/10 18:48:40 by zel-kass         ###   ########.fr       */
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
	long	count;
	long	die;
	long	eat;
	long	sleep;
	long	meals;
}			t_global;

typedef struct s_philo
{
	int			id;
	t_global	*global;
	pthread_t	thread;
}			t_philo;

//#######################################################//
//# 						INIT 						#//
//#######################################################//

t_global	*get_global(char **argv);
t_philo		*init_philo(t_global *global);

//#######################################################//
//# 					   PARSING						#//
//#######################################################//

int		ft_isdigit(char *str);
int		check_args(char **argv);

//#######################################################//
//# 					   ROUTINE						#//
//#######################################################//

void		*routine(void *ptr);

//#######################################################//
//# 						UTILS						#//
//#######################################################//

long		ft_atol(char *str);

#endif