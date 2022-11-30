/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:13:56 by zel-kass          #+#    #+#             */
/*   Updated: 2022/11/30 17:42:05 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*get_philo(char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->p_nb = ft_atol(argv[1]);
	philo->t_td = ft_atol(argv[2]);
	philo->t_te = ft_atol(argv[3]);
	philo->t_ts = ft_atol(argv[4]);
	if (argv[5])
		philo->n_eat = ft_atol(argv[5]);
	return (philo);
}