/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:07:32 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/18 02:06:39 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	finish_eat(t_philo *philo, int i, int cmp)
{
	pthread_mutex_lock(&philo->init->m_nb_eat);
	if (philo[i].nb_must_eat == 0)
	{
		cmp++;
		if (cmp == philo->init->nb_philo)
		{
			pthread_mutex_unlock(&philo->init->m_nb_eat);
			return (-1);
		}
	}
	pthread_mutex_unlock(&philo->init->m_nb_eat);
	return (cmp);
}

int	is_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->init->m_die);
	if (philo[i].time_to_die <= get_time())
	{
		pthread_mutex_lock(&philo->init->m_read);
		printf("%ld %d died \n", \
		get_time() - philo->init->time, philo[i].id);
		pthread_mutex_unlock(&philo->init->m_read);
		i = 0;
		while (i < philo->init->nb_philo)
		{
			philo[i].init->die = DIE;
			i++;
		}
		pthread_mutex_unlock(&philo->init->m_die);
		return (1);
	}
	pthread_mutex_unlock(&philo->init->m_die);
	return (0);
}

void	*monitoring_die(void *a)
{
	t_philo	*philo;
	int		i;
	int		cmp;

	cmp = 0;
	i = 0;
	philo = a;
	while (1)
	{
		while (i < philo->init->nb_philo)
		{
			cmp = finish_eat(philo, i, cmp);
			if (cmp == -1)
				return (NULL);
			if (is_dead(philo, i))
				return (NULL);
			i++;
			usleep(100);
		}
		i = 0;
	}
}

t_philo	*create_monitor(t_philo *philo)
{
	int			ret;
	pthread_t	monitor_time_die;

	ret = pthread_create(&monitor_time_die, NULL, &monitoring_die, philo);
	if (ret)
	{
		ft_printf("Probleme crea monitoring");
		free_all(philo);
		return (NULL);
	}
	philo->init->monitor_time_die = monitor_time_die;
	return (philo);
}

int	join_monitor(t_philo *philo)
{
	int			ret;

	ret = pthread_join(philo->init->monitor_time_die, NULL);
	if (ret)
	{
		ft_printf("Probleme join thread");
		return (1);
	}
	return (0);
}
