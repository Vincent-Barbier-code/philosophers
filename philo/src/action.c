/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:34:28 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/07 13:47:39 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->init.fork[philo->lfork]); // pas sur
	if (philo->init.die == DIE)
		pthread_mutex_unlock(&philo->init.fork[philo->lfork]);
	else
	{
		printf("%ld %d has taken a fork \n", get_time() - philo->init.time, philo->ID);
		pthread_mutex_lock(&philo->init.fork[philo->rfork]);
		printf("%ld %d has taken a fork \n", get_time() - philo->init.time, philo->ID);
		philo->nb_must_eat = philo->nb_must_eat - 1;
		philo->time_to_die = get_time() + philo->init.time_to_die;
		printf("%ld %d is eating \n", get_time() - philo->init.time, philo->ID);
		usleep(philo->init.time_to_eat * 1000);
		philo->state = DORT;
		pthread_mutex_unlock(&philo->init.fork[philo->lfork]);
		pthread_mutex_unlock(&philo->init.fork[philo->rfork]);
	}
}

void	*action(t_philo *philo)
{
	while (1)
	{
		if (philo->init.die == DIE)
			return (NULL);
		if(philo->nb_must_eat == 0)
			return (NULL);
		if (philo->ID % 2 == 1 && philo->state == -1)
			philo->state = DORT;
		if (philo->ID % 2 == 0 && philo->state == -1)
			eat(philo);
		if (philo->state == PENSE && !(philo->init.die == DIE))
			eat(philo);
		if (philo->state == DORT && !(philo->init.die == DIE))
		{
			printf("%ld %d is sleeping \n", get_time() - philo->init.time, philo->ID);
			usleep(philo->init.time_to_sleep * 1000);
			//if(!(philo->init.die == DIE))
			//{
				printf("%ld %d is thinking \n", get_time() - philo->init.time, philo->ID);
				philo->state = PENSE;
			//}
		}
	}
}
