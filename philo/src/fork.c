/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:20:06 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/07 01:24:33 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t	*init_fork(t_init *init)
{
	pthread_mutex_t	*fork;
	int i;
	int ret;

	fork = malloc(init->nb_philo * sizeof(pthread_mutex_t));
	i = 0;
	while (i < init->nb_philo)
	{
		ret = pthread_mutex_init(&fork[i], NULL);
		if (ret)
			return (NULL);
		i++;
	}
	return (fork);
}

void	destroy_fork(t_init *init)
{
	int i;

	i = 0;
	while (i < init->nb_philo)
	{
		pthread_mutex_destroy(&init->fork[i]);
		i++;
	}
}

unsigned long int	get_time(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
