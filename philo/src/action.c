/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 00:34:28 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/17 23:16:51 by vbarbier         ###   ########.fr       */
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

void	p_read(t_philo *philo, int what)
{
	pthread_mutex_lock(&philo->init->m_read);
	if (what == 0)
		printf("%ld %d has taken a fork \n", get_time() - philo->init->time, philo->ID);
	if (what == 1)
		printf("%ld %d is eating \n", get_time() - philo->init->time, philo->ID);
	if (what == 2)
		printf("%ld %d is sleeping \n", get_time() - philo->init->time, philo->ID);
	if (what == 3)
		printf("%ld %d is thinking \n", get_time() - philo->init->time, philo->ID);
	pthread_mutex_unlock(&philo->init->m_read);
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
			pthread_mutex_unlock(&philo->init->fork[philo->lfork]);
			pthread_mutex_unlock(&philo->init->fork[philo->rfork]);
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
		pthread_mutex_unlock(&philo->init->fork[philo->lfork]);
		pthread_mutex_unlock(&philo->init->fork[philo->rfork]);
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

int init_impair(t_philo *philo)
{
	if (philo->ID % 2 == 1)
	{	
		if (philo->state == -1)	
			return (1);
	}
	return (0);
}

int init_pair(t_philo *philo)
{
	if (philo->ID % 2 == 0)
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
	if (philo->state == PENSE && !(philo->init->die == DIE) && !(philo->nb_must_eat == 0) && philo->init->nb_philo != 1)
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
	if (philo->state == DORT && !(philo->init->die == DIE) && !(philo->nb_must_eat == 0))
	{
		pthread_mutex_unlock(&philo->init->m_die);
		pthread_mutex_unlock(&philo->init->m_nb_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->init->m_die);
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
		if (init_pair(philo)) //  
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
