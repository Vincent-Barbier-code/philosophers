/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 01:44:26 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/18 02:06:39 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	die(t_philo *philo)
{
	pthread_mutex_lock(&philo->init->m_die);
	if (philo->init->die == DIE)
	{
		pthread_mutex_unlock(&philo->init->m_die);
		return (1);
	}
	pthread_mutex_unlock(&philo->init->m_die);
	return (0);
}

int	init_impair(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{	
		if (philo->state == -1)
			return (1);
	}
	return (0);
}

int	init_pair(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (philo->state == -1 && philo->init->nb_philo != 1)
			return (1);
	}
	return (0);
}

int	can_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->init->m_die);
	pthread_mutex_lock(&philo->init->m_nb_eat);
	if (philo->state == PENSE && !(philo->init->die == DIE) \
	&& !(philo->nb_must_eat == 0) && philo->init->nb_philo != 1)
	{
		pthread_mutex_unlock(&philo->init->m_die);
		pthread_mutex_unlock(&philo->init->m_nb_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->init->m_die);
	pthread_mutex_unlock(&philo->init->m_nb_eat);
	return (0);
}

int	can_sleep(t_philo *philo)
{	
	pthread_mutex_lock(&philo->init->m_die);
	pthread_mutex_lock(&philo->init->m_nb_eat);
	if (philo->state == DORT && !(philo->init->die == DIE) \
	&& !(philo->nb_must_eat == 0))
	{
		pthread_mutex_unlock(&philo->init->m_die);
		pthread_mutex_unlock(&philo->init->m_nb_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->init->m_die);
	pthread_mutex_unlock(&philo->init->m_nb_eat);
	return (0);
}
