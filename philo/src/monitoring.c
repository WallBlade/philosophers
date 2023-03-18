/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:52:41 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/18 16:18:10 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	state(time_t last_meal, t_philo *philo)
{
	time_t	now;

	now = timer() - last_meal;
	if (now >= philo->t_die / 1000)
	{
		print_status(philo, "died");
		return (DEATH);
	}
	return (ALIVE);
}

int	runner(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_lock(&philo[i].eat);
		if (state(philo[i].last_meal, &philo[i]) == DEATH)
		{
			pthread_mutex_unlock(&philo[i].eat);
			pthread_mutex_lock(&philo->global->death);
			philo->global->is_dead = DEATH;
			pthread_mutex_unlock(&philo->global->death);
			return (DEATH);
		}
		pthread_mutex_unlock(&philo[i].eat);
		i++;
	}
	return (ALIVE);
}

int	everyone_ate(t_philo *philo, int count)
{
	int	i;
	int	round;

	i = 0;
	round = 0;
	while (i < count)
	{
		pthread_mutex_lock(&philo[i].meal);
		if (philo[i].meals == philo->global->round)
			round++;
		pthread_mutex_unlock(&philo[i].meal);
		i++;
	}
	if (round == philo->global->count - 1)
		return (DEATH);
	return (ALIVE);
}

void	*manager(t_philo *philo, int count)
{
	int		hungry_mode;

	hungry_mode = philo->global->god_mode;
	while (1)
	{
		if (runner(philo, count) == DEATH)
			return (NULL);
		if (hungry_mode == 1)
		{
			if (everyone_ate(philo, count) == DEATH)
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
