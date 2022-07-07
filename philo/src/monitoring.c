/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:07:32 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/07 06:48:45 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitoring(void *a)
{
	t_philo			*philo;
	pthread_mutex_t	mutex;
	int				i;

	i = 0;
	philo = a;
	pthread_mutex_init(&mutex, NULL);
	//usleep(100000);
	while (1)
	{
		while (i < philo->init.nb_philo)
		{
			pthread_mutex_lock(&mutex);
			if (philo[i].time_to_die <= get_time())
			{
				printf("%ld %d died \n", get_time() - philo->init.time, philo[i].ID);
				i = 0;
				while (i < philo->init.nb_philo)
				{
				//	printf ("philo meurt %d \n", philo[i].ID);
					philo[i].init.die = DIE;
				//	printf ("philo state %d \n", philo[i].init.die);
					i++;
				//	exit(1);
				}
				return (NULL);
				//printf("%ld, BOOM, %ld, %ld", philo[i].time_to_die, get_time(), get_time() - philo[i].time_to_die);
				//exit(1);
			}
			i++;
			pthread_mutex_unlock(&mutex);
			//usleep(100);
		}
		i = 0;
	}
}

void	create_monitor(t_philo *philo)
{
	int			ret;
	pthread_t	monitor;
	
	ret = pthread_create(&monitor, NULL, &monitoring, philo);
	if (ret)
	{
		ft_printf("Probleme crea monitoring");
		//return (i);
	}
}