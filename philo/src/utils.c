/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:32:11 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/16 15:32:05 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_exit(char *str, void *ptr)
{
	printf("%s", str);
	free(ptr);
	exit(EXIT_FAILURE);
}

int	state(t_philo philo)
{
	time_t	now;

	now = timer()- philo.last_meal;
	if (now >= philo.global->die / 1000)
	{
		print_status(&philo, "died");
		return (DEATH);
	}
	return (ALIVE);
}

time_t	timer(void)
{
	struct timeval	time;
	time_t			current;

	gettimeofday(&time, NULL);
	current = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current);
}

int	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->global->death);
	if (philo->global->is_dead == DEATH)
	{
		pthread_mutex_unlock(&philo->global->death);
		return (DEATH);
	}
	pthread_mutex_unlock(&philo->global->death);
	pthread_mutex_lock(&philo->global->msg);
	printf("%ld %d ", timer() - philo->global->start, philo->id + 1);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->global->msg);
	return (ALIVE);
}

void	destroy_everything(t_philo *philo, t_global *global)
{
	int	i;

	i = 0;
	while (i < global->count)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(&philo[i].eat);
		i++;
	}
	free(philo);
	pthread_mutex_destroy(&global->death);
	pthread_mutex_destroy(&global->msg);
	free(global);
}
