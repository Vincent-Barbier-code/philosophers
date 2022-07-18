/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:34:28 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/18 02:06:39 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	p_read(t_philo *philo, int what)
{
	pthread_mutex_lock(&philo->init->m_read);
	if (what == 0)
		printf("%ld %d has taken a fork \n", \
		get_time() - philo->init->time, philo->id);
	if (what == 1)
		printf("%ld %d is eating \n", \
		get_time() - philo->init->time, philo->id);
	if (what == 2)
		printf("%ld %d is sleeping \n", \
		get_time() - philo->init->time, philo->id);
	if (what == 3)
		printf("%ld %d is thinking \n", \
		get_time() - philo->init->time, philo->id);
	pthread_mutex_unlock(&philo->init->m_read);
}

void	unlock_db_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->init->fork[philo->lfork]);
	pthread_mutex_unlock(&philo->init->fork[philo->rfork]);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->init->fork[philo->lfork]);
	if (die(philo))
		pthread_mutex_unlock(&philo->init->fork[philo->lfork]);
	else
	{
		p_read(philo, 0);
		pthread_mutex_lock(&philo->init->fork[philo->rfork]);
		if (die(philo))
		{
			unlock_db_fork(philo);
			return ;
		}	
		p_read(philo, 0);
		pthread_mutex_lock(&philo->init->m_nb_eat);
		philo->nb_must_eat = philo->nb_must_eat - 1;
		pthread_mutex_unlock(&philo->init->m_nb_eat);
		pthread_mutex_lock(&philo->init->m_die);
		philo->time_to_die = get_time() + philo->init->time_to_die;
		pthread_mutex_unlock(&philo->init->m_die);
		p_read(philo, 1);
		usleep(philo->init->time_to_eat * 1000);
		philo->state = DORT;
		unlock_db_fork(philo);
	}
}

int	nb_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->init->m_nb_eat);
	if (philo->nb_must_eat == 0)
	{
		pthread_mutex_unlock(&philo->init->m_nb_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->init->m_nb_eat);
	return (0);
}

void	*action(t_philo *philo)
{
	while (1)
	{
		if (die(philo))
			return (NULL);
		if (nb_eat(philo))
			return (NULL);
		if (init_impair(philo))
			philo->state = DORT;
		if (init_pair(philo))
			eat(philo);
		if (can_eat(philo))
			eat(philo);
		if (can_sleep(philo))
		{
			p_read(philo, 2);
			if (die(philo))
				return (NULL);
			usleep(philo->init->time_to_sleep * 1000);
			if (die(philo))
				return (NULL);
			p_read(philo, 3);
				philo->state = PENSE;
		}
	}
}
