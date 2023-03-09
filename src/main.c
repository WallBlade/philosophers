/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-kass <zel-kass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:42:33 by zel-kass          #+#    #+#             */
/*   Updated: 2023/01/30 17:58:18 by zel-kass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_global	*global;

	if (argc > 6 || argc < 5)
		return (printf("Wrong arguments number\n"), 0);
	global = get_global(argv);
	printf("nb = %ld\ttd = %ld\t te = %ld\tts = %ld\teat = %ld\n", global->p_nb, global->t_td, global->t_te, global->t_ts, global->n_eat);
	return (0);
}