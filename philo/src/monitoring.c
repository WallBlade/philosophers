/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:52:41 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/14 17:32:20 by zel-kass         ###   ########.fr       */
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
		if (state(philo[i]) == DEATH)
		{
			pthread_mutex_lock(&philo->global->death);
			philo->global->is_dead = DEATH;
			pthread_mutex_unlock(&philo->global->death);
			break ;
		}
		if (i == philo->global->count)
			i = 0;
		printf("i = %d\n", i);
		i++;
	}
	return (NULL);
}
