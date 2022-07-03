/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:20:06 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/03 00:55:53 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	*init_fork(t_philo philo)
{
	int *fork;
	int i;

	fork = malloc(philo.init.nb_philo * sizeof(int));
	i = 0;
	while (i < philo.init.nb_philo)
	{
		fork[i] = 1;
		i++;
	}
	return (fork);
}
