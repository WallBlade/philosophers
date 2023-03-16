/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:45:43 by zel-kass          #+#    #+#             */
/*   Updated: 2023/01/30 17:45:43 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_global	*get_global(char **argv)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!global || !check_args(argv))
		return (NULL);
	global->count = ft_atol(argv[1]);
	if (global->count < 1)
		clean_exit("No one's arround the table\n", global);
	global->start = (time_t)timer();
	global->die = ft_atol(argv[2]) * 1000;
	global->eat = ft_atol(argv[3]) * 1000;
	global->sleep = ft_atol(argv[4]) * 1000;
	global->think = global->die - (global->eat + global->sleep) / 2;
	if (global->think <= 0)
		global->think = 0;
	global->is_dead = 1;
	pthread_mutex_init(&global->msg, NULL);
	pthread_mutex_init(&global->meal, NULL);
	pthread_mutex_init(&global->death, NULL);
	if (argv[5])
		global->round = ft_atol(argv[5]);
	else
		global->round = 0;
	return (global);
}

void	init_thread(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
}

void	init_mutex(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philo[i].left_fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(&philo[i].eat, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		i++;
	}
}

void	connect_mutex(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		philo[i].right_fork = philo[i + 1].left_fork;
		if (i == count - 1)
			philo[i].right_fork = philo[0].left_fork;
		i++;
	}
}

t_philo	*init_philo(t_global *global)
{
	int		i;
	int		count;
	t_philo	*philo;

	i = 0;
	count = global->count;
	philo = malloc(sizeof(t_philo) * count);
	if (!philo)
		return (NULL);
	while (i < count)
	{
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].global = global;
		philo[i].last_meal = timer();
		i++;
	}
	init_mutex(philo, count);
	connect_mutex(philo, count);
	init_thread(philo, count);
	return (philo);
}
