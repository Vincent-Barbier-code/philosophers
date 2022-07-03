/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:59:31 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/03 02:31:08 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *a)
{
	t_philo philo = *(t_philo *) a;

	usleep(1);
	pthread_mutex_lock(&philo.init.mutex);
	printf("%d \n", philo.init.nb_philo);
	pthread_mutex_unlock(&philo.init.mutex);
	return NULL;
}

t_philo init_philo(t_philo *philo, t_init init, int i)
{
	pthread_t thread;

	philo[i].ID = i;
	philo[i].state = -1;
	philo[i].nb_must_eat = philo->init.nb_must_eat;
	philo[i].thread = thread;
	return (philo[i]);
}

int	create_philo(t_philo *philo)
{
	int			ret;
	int			i;

	pthread_mutex_init(philo[0].init.mutex, NULL);
	philo = malloc(philo[0].init.nb_philo * sizeof(philo));
	i = 0;
	ret = 0;
	printf ("Creation des threads clients !\n");
	while(i < init->nb_philo)
	{
		philo[i] = init_philo(philo, *init, i);
		ret = pthread_create(philo[i].thread, NULL, routine, &i);
		if (ret)
		{
			ft_printf("Probleme crea thread");
			return (i);
		}
		i++;
	}
	return (0);
}

int	join_philo(t_philo *philo)
{
	int			ret;
	int			i;

	i = 0;
	while (i < philo[0].init.nb_philo)
	{
		ret = pthread_join(philo[i].thread, NULL);
		if (ret)
		{
			ft_printf("Probleme join thread");
			return (i);
		}
		i++;
	}
	return (0);
}

float	time_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec));
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, NULL);
	parsing(ac, av, &philo->init);
	if (create_philo(&philo))
		return (EXIT_FAILURE); // free le tab detruire thread
	if (join_philo(&philo))
		return (EXIT_FAILURE); // free le tab detruire thread

	gettimeofday(&end, NULL);
	
    printf("timestamp_in_ms: %0.4f ms\n", time_diff(&start, &end)* 1e3);
	ft_printf("%d ", init.nb_philo);
	ft_printf("%d ", init.time_to_die);
	ft_printf("%d ", init.time_to_eat);
	ft_printf("%d ", init.time_to_sleep);
	if (init.nb_must_eat != 0)
		ft_printf("%d ", init.nb_must_eat);
	
	ft_printf("\n--------------------------FIN-------------------------");
	return(EXIT_SUCCESS);
}