/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:32:11 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/14 17:31:49 by zel-kass         ###   ########.fr       */
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

	now = timer();
	if (now - philo.last_meal >= philo.global->die)
	{
		print_status(&philo, "is dead");
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
	pthread_mutex_lock(&philo->global->msg);
	pthread_mutex_lock(&philo->global->death);
	if (philo->global->is_dead == DEATH)
	{
		pthread_mutex_unlock(&philo->global->msg);
		pthread_mutex_unlock(&philo->global->death);
		return (DEATH);
	}
	printf("philo %d ", philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->global->msg);
	pthread_mutex_unlock(&philo->global->death);
	return (ALIVE);
}

void	destroy_everything(t_philo *philo, t_global *global)
{
	int	i;

	i = 0;
	while (i < global->count)
	{
		pthread_mutex_destroy(&philo[i].fork);
		pthread_mutex_destroy(&philo[i].eat);
		i++;
	}
	free(philo);
	pthread_mutex_destroy(&global->death);
	pthread_mutex_destroy(&global->msg);
	free(global);
}
