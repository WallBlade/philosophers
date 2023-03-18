/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:52:41 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/18 21:44:59 by zel-kass         ###   ########.fr       */
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

int	check_end(t_philo *philo, int res, int count)
{
	if (res == count)
	{
		pthread_mutex_lock(&philo->global->end);
		philo->global->round = FINISH;
		pthread_mutex_unlock(&philo->global->end);
		return (DEATH);
	}
	return (ALIVE);
}

int	everyone_ate(t_philo *philo, int count)
{
	int	i;
	int	res;
	int	round;
	int	meals;

	i = 0;
	res = 0;
	pthread_mutex_lock(&philo[i].meal);
	round = philo[i].meals;
	pthread_mutex_unlock(&philo[i].meal);
	meals = round;
	while (i < count)
	{
		if (round == philo->global->round)
		{
			if (meals == round)
				res++;
			pthread_mutex_lock(&philo[i].meal);
			meals = philo[i].meals;
			pthread_mutex_unlock(&philo[i].meal);
		}
		i++;
	}
	return (check_end(philo, res, count));
}

void	*manager(t_philo *philo, int count, int mode)
{
	while (1)
	{
		if (runner(philo, count) == DEATH)
			return (NULL);
		if (mode == 1)
		{
			if (everyone_ate(philo, count) == DEATH)
				return (NULL);
		}
		sleep_like_a_baby(1000);
	}
	return (NULL);
}
