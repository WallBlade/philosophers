/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:42:33 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/14 17:24:15 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waitforme(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	diner(char **argv)
{
	t_global	*global;
	t_philo		*philo;

	check_args(argv);
	global = get_global(argv);
	philo = init_philo(global);
	pthread_create(&global->manager, NULL, &manager, philo);
	waitforme(philo, global->count);
	pthread_join(global->manager, NULL);
	destroy_everything(philo, global);
}

int	main(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		return (printf("Wrong arguments number\n"), 0);
	diner(argv);
	return (DEATH);
}
