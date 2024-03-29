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

int	even_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_status(philo, "has taken a fork") == DEATH)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (DEATH);
	}
	pthread_mutex_lock(philo->right_fork);
	if (print_status(philo, "has taken a fork") == DEATH)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (DEATH);
	}
	return (ALIVE);
}

int	odd_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (print_status(philo, "has taken a fork") == DEATH)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (DEATH);
	}
	pthread_mutex_lock(philo->left_fork);
	if (print_status(philo, "has taken a fork") == DEATH)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (DEATH);
	}
	return (ALIVE);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat);
	philo->last_meal = timer();
	pthread_mutex_unlock(&philo->eat);
	if (print_status(philo, "is eating") == DEATH)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (DEATH);
	}
	sleep_like_a_baby(philo->t_eat);
	pthread_mutex_lock(&philo->meal);
	philo->meals += 1;
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (ALIVE);
}

int	sleeping(t_philo *philo)
{
	if (print_status(philo, "is sleeping") == DEATH)
		return (DEATH);
	sleep_like_a_baby(philo->t_sleep);
	if (print_status(philo, "is thinking") == DEATH)
		return (DEATH);
	sleep_like_a_baby((philo->t_eat - philo->t_sleep)
		* ((philo->t_eat - philo->t_sleep) > 0));
	sleep_like_a_baby(1500);
	return (ALIVE);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->id % 2 == 0)
		sleep_like_a_baby(philo->t_eat / 2);
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			if (even_fork(philo) == DEATH)
				break ;
		}
		else
		{
			if (odd_fork(philo) == DEATH)
				break ;
		}
		if (eating(philo) == DEATH)
			break ;
		if (sleeping(philo) == DEATH)
			break ;
	}
	return (NULL);
}
