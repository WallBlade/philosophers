/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:46:54 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/15 18:37:32 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define DEATH 0
# define ALIVE 1
# define ERROR -1

typedef struct s_global
{
	long			count;
	long			die;
	long			eat;
	long			sleep;
	long			round;
	int				is_dead;
	time_t			start;
	pthread_t		manager;
	pthread_mutex_t	death;
	pthread_mutex_t	msg;
}			t_global;

typedef struct s_philo
{
	int				id;
	int				meals;
	time_t			last_meal;
	t_global		*global;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat;
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

int			take_fork(t_philo *philo);
int			eating(t_philo *philo);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);
void		*routine(void *ptr);

//#######################################################//
//# 					  MONITORING					#//
//#######################################################//

void		*manager(void *ptr);

//#######################################################//
//# 						UTILS						#//
//#######################################################//

void		clean_exit(char *str, void *ptr);
int			state(t_philo philo);
time_t		timer(void);
int			print_status(t_philo *philo, char *str);
void		destroy_everything(t_philo *philo, t_global *global);

#endif