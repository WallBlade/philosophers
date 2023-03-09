/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:45:43 by zel-kass          #+#    #+#             */
/*   Updated: 2023/01/30 17:45:43 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_global	*get_global(char **argv)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!global || !check_args(argv))
		return (NULL);
	global->p_nb = ft_atol(argv[1]);
	global->t_td = ft_atol(argv[2]);
	global->t_te = ft_atol(argv[3]);
	global->t_ts = ft_atol(argv[4]);
	if (argv[5])
		global->n_eat = ft_atol(argv[5]);
	return (global);
}

void    init_threads(t_philo *philo, t_data *global)
{
    int i;

    i = 0; 
    while (i < global->p_nb)
    {
        pthread_create(philo.data[i]->thread, NULL, routine, philo->data[i]);
        i++;
    }
}
