/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:32:11 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/13 17:27:50 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->global->msg);
	printf("philo %d ", philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->global->msg);
}