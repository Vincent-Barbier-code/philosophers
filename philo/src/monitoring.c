/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:07:32 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/17 22:39:28 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitoring_die(void *a)
{
	t_philo			*philo;
	int				i;
	int cmp;
	//pthread_mutex_t	mutex;

	cmp = 0;
	i = 0;
	philo = a;
	//pthread_mutex_init(&mutex, NULL);
	while (1)
	{
		while (i < philo->init->nb_philo)
		{
		//	pthread_mutex_lock(&mutex);
			pthread_mutex_lock(&philo->init->m_nb_eat);
			if (philo[i].nb_must_eat == 0)
			{
				cmp++;
				if (cmp == philo->init->nb_philo)
				{
					pthread_mutex_unlock(&philo->init->m_nb_eat);
					return (NULL);
				}
			}
			pthread_mutex_unlock(&philo->init->m_nb_eat);
			pthread_mutex_lock(&philo->init->m_die);
			if (philo[i].time_to_die <= get_time())
			{
				pthread_mutex_lock(&philo->init->m_read);
				printf("%ld %d died \n", get_time() - philo->init->time, philo[i].ID);
				pthread_mutex_unlock(&philo->init->m_read);
				i = 0;
				while (i < philo->init->nb_philo)
				{
					philo[i].init->die = DIE;
					i++;
				}
				//pthread_mutex_unlock(&mutex);
				pthread_mutex_unlock(&philo->init->m_die);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->init->m_die);
			i++;
			//pthread_mutex_unlock(&mutex);
			usleep(100);
		}
		i = 0;
		//cmp = 0;
	}
}

t_philo	*create_monitor(t_philo *philo)
{
	int			ret;
	pthread_t	monitor_time_die;
	//pthread_t	monitor_nb_eat;

	
	ret = pthread_create(&monitor_time_die, NULL, &monitoring_die, philo);
	if (ret)
	{
		ft_printf("Probleme crea monitoring");
		//return (i);
	}
	/*
	ret = pthread_create(&monitor_nb_eat, NULL, &monitoring_eat, philo);
	if (ret)
	{
		ft_printf("Probleme crea monitoring");
		//return (i);
	}
	*/
	//philo->init->monitor_nb_eat = monitor_nb_eat;
	philo->init->monitor_time_die = monitor_time_die;
	return (philo);
}

int	join_monitor(t_philo *philo)
{
	int			ret;
	
	ret = pthread_join(philo->init->monitor_time_die , NULL);
	if (ret)
	{
		ft_printf("Probleme join thread");
		return (1);
	}
	// ret = pthread_join(philo->init->monitor_nb_eat , NULL);
	// if (ret)
	// {
	// 	ft_printf("Probleme join thread");
	// 	return (1);
	// }
	return (0);
}
