/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:59:31 by vbarbier          #+#    #+#             */
/*   Updated: 2022/06/10 20:46:13 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//int pthread_create (pthread_t * thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);

int x = 0;

static void *philosophe(void *i)
{
	ft_printf("Philo %p !\n", i);
	x++;
	ft_printf("x = %d\n", x);
	return NULL;
}


void	create_philo(t_init *init)
{
	pthread_t	philo[init->nb_philo];
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	if (!ret)
	{
		printf ("Creation des threads clients !\n");
		while(i < init->nb_philo)
		{
			ret = pthread_create(&philo[i], NULL, philosophe, &i);
			if (ret)
				ft_printf("OULA1");
			ret = pthread_join(philo[i], NULL);
			if (ret)
				ft_printf("OULA2");
			i++;
		}
	}
	else
	{
		ft_printf ("OULA3");
	}
	ft_printf("fianl x = %d\n", x);
}


int	main(int ac, char **av)
{
	t_init	init;

	parsing(ac, av, &init);
//	create_philo(&init);

	
	ft_printf("%d ", init.nb_philo);
	ft_printf("%d ", init.time_to_die);
	ft_printf("%d ", init.time_to_eat);
	ft_printf("%d ", init.time_to_sleep);
	ft_printf("%d ", init.nb_must_eat);
	ft_printf("\n--------------------------FINIS-------------------------");
	exit(EXIT_SUCCESS);
}