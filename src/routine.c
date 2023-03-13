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

void	take_fork(t_philo *philo)
{
	int	i;

	i = philo->id;
	if (i % 2 && !philo->has_eaten)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo[i + 1].fork);
		print_status(philo, "has taken a fork");
		eating(philo);
	}
	else if (i % 3 && !philo->has_eaten)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo[i - 1].fork);
		print_status(philo, "has taken a fork");
		eating(philo);
	}
}

void	eating(t_philo *philo)
{
	int	i;

	i = philo->id;
	print_status(philo, "is eating");
	usleep(philo->global->eat);
	if (i % 2)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo[i + 1].fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo[i - 1].fork);
	}
	philo->has_eaten = 1;
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->global->sleep);
	philo->has_eaten = 0;
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking");
	usleep(philo->global->die);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2)
	{
		printf("id = %d\n", philo->id);
		usleep(200);
	}
	while (1)
	{
		take_fork(philo);
		sleeping(philo);
		thinking(philo);
	}
}
