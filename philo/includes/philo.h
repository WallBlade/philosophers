/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:46:54 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/18 18:45:32 by zel-kass         ###   ########.fr       */
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
# define FINISH -1

typedef struct s_global
{
	long			count;
	long			die;
	long			eat;
	long			sleep;
	long			round;
	int				is_dead;
	int				mode;
	time_t			start;
	pthread_mutex_t	end;
	pthread_mutex_t	msg;
	pthread_mutex_t	death;
}			t_global;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	time_t			last_meal;
	t_global		*global;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	eat;
	pthread_mutex_t	meal;
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

int			state(time_t last_meal, t_philo *philo);
void		*manager(t_philo *philo, int count, int mode);

//#######################################################//
//# 						UTILS						#//
//#######################################################//

int			sleep_like_a_baby(time_t rest);
void		clean_exit(char *str, void *ptr);
time_t		timer(void);
int			print_status(t_philo *philo, char *str);
void		destroy_everything(t_philo *philo, t_global *global);

#endif