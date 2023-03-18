/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:32:11 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/18 21:01:04 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_like_a_baby(time_t rest)
{
	struct timeval	tv;
	struct timeval	start;
	long int		need;

	gettimeofday(&start, NULL);
	need = 0;
	rest /= 1000;
	while (need < rest)
	{
		gettimeofday(&tv, NULL);
		need = (tv.tv_sec - start.tv_sec) * 1000
			+ (tv.tv_usec - start.tv_usec) / 1000;
		usleep(30);
	}
	return (1);
}

void	clean_exit(char *str, void *ptr)
{
	printf("%s", str);
	free(ptr);
	exit(EXIT_FAILURE);
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
	pthread_mutex_lock(&philo->global->end);
	if (philo->global->round == FINISH)
	{
		pthread_mutex_unlock(&philo->global->end);
		return (DEATH);
	}
	pthread_mutex_unlock(&philo->global->end);
	pthread_mutex_lock(&philo->global->msg);
	printf("%ld %d %s\n", timer() - philo->global->start, philo->id + 1, str);
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
		free(philo[i].left_fork);
		pthread_mutex_destroy(&philo[i].eat);
		pthread_mutex_destroy(&philo[i].meal);
		i++;
	}
	free(philo);
	pthread_mutex_destroy(&global->death);
	pthread_mutex_destroy(&global->msg);
	pthread_mutex_destroy(&global->end);
	free(global);
}
