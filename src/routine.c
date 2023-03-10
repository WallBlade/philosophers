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
	printf("philo %d has taken a fork\n", philo->id);
}

void	eating(t_philo *philo)
{
	printf("philo %d is eating\n", philo->id);
}

void	sleeping(t_philo *philo)
{
	printf("philo %d is sleeping\n", philo->id);
}

void	thinking(t_philo *philo)
{
	printf("philo %d is thinking\n", philo->id);
}

void    *routine(void *ptr)
{
    t_philo *philo;

    philo = ptr;
    while (1)
    {
		take_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
    }
}
