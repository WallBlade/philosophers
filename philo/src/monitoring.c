/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:52:41 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/15 15:17:12 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager(void *ptr)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = ptr;
	while (1)
	{
		i = 0;
		while ( i < philo->global->count)
		{
			if (state(philo[i]) == DEATH)
			{
				pthread_mutex_lock(&philo->global->death);
				philo->global->is_dead = DEATH;
				pthread_mutex_unlock(&philo->global->death);
				return (NULL) ;
			}
			i++;
		}
		usleep(2000500500);
	}
	return (NULL);
}
