/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:46:54 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/13 17:21:39 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_global
{
	long			count;
	long			die;
	long			eat;
	long			sleep;
	long			meals;
	time_t			start;
	pthread_mutex_t	msg;
}			t_global;

typedef struct s_philo
{
	int				id;
	int				has_eaten;
	t_global		*global;
	pthread_mutex_t	fork;
	pthread_t		thread;
	struct s_philo	*next;
	struct s_philo	*prev;
}			t_philo;

//#######################################################//
//# 						INIT 						#//
//#######################################################//

t_global	*get_global(char **argv);
t_philo		*init_philo(t_global *global);

//#######################################################//
//# 					   PARSING						#//
//#######################################################//

long		ft_atol(char *str);
int			ft_isdigit(char *str);
int			check_args(char **argv);

//#######################################################//
//# 					   ROUTINE						#//
//#######################################################//

void		take_fork(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		*routine(void *ptr);

//#######################################################//
//# 						UTILS						#//
//#######################################################//

void		print_status(t_philo *philo, char *str);
void		clean_exit(char *str, void *ptr);
time_t		timer(void);

#endif