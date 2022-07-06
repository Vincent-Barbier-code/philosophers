/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:59:31 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/07 01:04:21 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	join_philo(t_philo *philo, t_init *init)
{
	int			ret;
	int			i;

	i = 0;
	while (i < init->nb_philo)
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

void	*routine(void *a)
{
	t_philo *philo;

	philo = a;
	action(philo);
	return (NULL);
}

t_philo init_philo(t_philo *philo, t_init init, int i)
{
	philo[i].ID = i;
	philo[i].state = -1;
	philo[i].init = init;
	philo[i].lfork = i;
	if (i == philo->init.nb_philo - 1)
		philo[i].rfork = 0;
	else
		philo[i].rfork = i + 1;
	if (init.nb_must_eat != 0)
		philo[i].nb_must_eat = philo->init.nb_must_eat;
	else
		philo[i].nb_must_eat = -1;
	return (philo[i]);
}

t_philo	*create_philo(t_philo *philo, t_init *init)
{
	int			ret;
	int			i;

	philo = malloc(init->nb_philo * sizeof(t_philo));
	i = 0;
	init->fork = init_fork(init);
	init->time = get_time();
	printf ("Creation des threads clients !\n");
	while(i < init->nb_philo)
	{
		philo[i] = init_philo(philo, *init, i);
		ret = pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		if (ret)
		{
			ft_printf("Probleme crea thread");
			//return (i);
		}
		i++;
	}
	return (philo);
}

int	main(int ac, char **av)
{
	t_philo				*philo;
	t_init				init;

	parsing(ac, av, &init);
	philo = NULL;
	philo = create_philo(philo, &init);
	 // free le tab
	if (join_philo(philo, &init))
		return (EXIT_FAILURE); // free le tab
	destroy_fork(&init);

	ft_printf("%d ", init.nb_philo);
	ft_printf("%d ", init.time_to_die);
	ft_printf("%d ", init.time_to_eat);
	ft_printf("%d ", init.time_to_sleep);
	if (init.nb_must_eat != 0)
		ft_printf("%d ", init.nb_must_eat);	
	
	ft_printf("\n--------------------------FIN-------------------------");
	return(EXIT_SUCCESS);
}