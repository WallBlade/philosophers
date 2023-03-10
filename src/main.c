/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:42:33 by zel-kass          #+#    #+#             */
/*   Updated: 2023/03/10 18:56:38 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waitforme(t_global *global, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < global->count)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_global	*global;
	t_philo		*philo;

	if (argc > 6 || argc < 5)
		return (printf("Wrong arguments number\n"), 0);
	global = get_global(argv);
	philo = init_philo(global);
	waitforme(global, philo);
	return (0);
}