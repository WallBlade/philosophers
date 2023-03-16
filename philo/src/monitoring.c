/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:52:41 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/16 15:32:36 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager(t_philo *philo, int count)
{
	int		i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < count)
		{
			pthread_mutex_lock(&philo[i].lock);
			if (state(philo[i]) == DEATH)
			{
				pthread_mutex_lock(&philo->global->death);
				philo->global->is_dead = DEATH;
				pthread_mutex_unlock(&philo->global->death);
				pthread_mutex_unlock(&philo[i].lock);
				return (NULL) ;
			}
			pthread_mutex_unlock(&philo[i].lock);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
