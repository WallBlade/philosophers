/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:25:04 by zel-kass          #+#    #+#             */
/*   Updated: 2023/01/30 17:25:04 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	pthread_mutex_lock(&philo[i].fork);
	if (print_status(philo, "has taken a fork") == DEATH)
	{
		dprintf(2, "COUCOU1\n");
		pthread_mutex_unlock(&philo[i].fork);
		return (DEATH);
	}
	if (i % 2)
		pthread_mutex_lock(&philo[i + 1].fork);
	else if (i % 3)
		pthread_mutex_lock(&philo[i - 1].fork);
	print_status(philo, "has taken a fork");
	if (eating(philo) == DEATH)
	{
		dprintf(2, "COUCOU2\n");
		pthread_mutex_unlock(&philo[i].fork);
		if (i % 2)
			pthread_mutex_unlock(&philo[i + 1].fork);
		else if (i % 3)
			pthread_mutex_unlock(&philo[i - 1].fork);
		return (DEATH);
	}
	return (ALIVE);
}

int	eating(t_philo *philo)
{
	int	i;

	i = philo->id;
	pthread_mutex_lock(&philo->eat);
	philo->last_meal = timer();
	pthread_mutex_unlock(&philo->eat);
	if (print_status(philo, "is eating") == DEATH)
	{
		dprintf(2, "COUCOU3\n");
		return (DEATH);
	}
	usleep(philo->global->eat);
	pthread_mutex_unlock(&philo[i].fork);
	if (i % 2)
		pthread_mutex_unlock(&philo[i + 1].fork);
	else if (i % 3)
		pthread_mutex_unlock(&philo[i - 1].fork);
	return (ALIVE);
}

int	sleeping(t_philo *philo)
{
	if (print_status(philo, "is sleeping") == DEATH)
		return (DEATH);
	usleep(philo->global->sleep);
	return (ALIVE);
}

int	thinking(t_philo *philo)
{
	if (print_status(philo, "is thinking") == DEATH)
		return (DEATH);
	return (ALIVE);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2)
		usleep(philo->global->eat / 2);
	while (1)
	{
		if (take_fork(philo) == DEATH)
			break ;
		if (sleeping(philo) == DEATH)
			break ;
		if (thinking(philo) == DEATH)
			break ;
	}
	return (NULL);
}
