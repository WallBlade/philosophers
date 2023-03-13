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
	global->die = ft_atol(argv[2]);
	global->eat = ft_atol(argv[3]);
	global->sleep = ft_atol(argv[4]);
	pthread_mutex_init(&global->msg, NULL);
	if (argv[5])
		global->meals = ft_atol(argv[5]);
	else
		global->meals = 0;
	return (global);
}

t_philo	*init_philo(t_global *global)
{
	int		i;
	int		index;
	t_philo	*philo;

	i = global->count;
	index = 0;
	philo = malloc(sizeof(t_philo) * i);
	if (!philo)
		return (NULL);
	while (i > 0)
	{
		philo[index].id = index + 1;
		philo[index].global = global;
		pthread_mutex_init(&philo[index].fork, NULL);
		pthread_create(&philo[index].thread, NULL, &routine, &philo[index]);
		index++;
		i--;
	}
	return (philo);
}
