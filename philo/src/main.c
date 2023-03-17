/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:42:33 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/17 19:01:30 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waitforme(t_philo *philo, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		pthread_join(philo[i].thread, NULL);
}

void	*akon(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	printf("%ld %d has taken a fork\n", timer() - philo->global->start, philo->id);
	usleep(philo->global->die);
	printf("%ld %d died\n", timer() - philo->global->start, philo->id);
	return (NULL);
}

void	lonely(t_global *global, t_philo *philo)
{
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return ;
	philo->id = 1;
	philo->meals = 0;
	philo->global = global;
	philo->last_meal = timer();
	pthread_create(&philo->thread, NULL, &akon, philo);
	pthread_join(philo->thread, NULL);
	free(philo);
	pthread_mutex_destroy(&philo->global->death);
	pthread_mutex_destroy(&philo->global->msg);
	free(global);
}

void	wokeupinthemiddleofthenight(char **argv)
{
	t_global	*global;
	t_philo		*philo;

	if (!check_args(argv))
		return ;
	philo = NULL;
	global = get_global(argv);
	if (global->count == 1)
		lonely(global, philo);
	else
	{
		philo = init_philo(global);
		manager(philo, global->count);
		waitforme(philo, global->count);
		destroy_everything(philo, global);
	}
}

int	main(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		return (printf("Wrong arguments number\n"), 0);
	wokeupinthemiddleofthenight(argv);
	return (DEATH);
}
