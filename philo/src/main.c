/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:59:31 by vbarbier          #+#    #+#             */
/*   Updated: 2022/06/11 00:34:23 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//int pthread_create (pthread_t * thread, pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);

unsigned long long int x = 0;
pthread_mutex_t	mutex;

static void *philosophe(void *i)
{
	
	int a;

	a = 0;
	while (a < 1)
	{
		pthread_mutex_lock(&mutex);
		x++;
		a++;
		pthread_mutex_unlock(&mutex);
	}
	
//	x++;
//	ft_printf("x = %d\n", x);
	return NULL;
}


void	create_philo(t_init *init)
{
	pthread_t	philo[init->nb_philo];
	
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	pthread_mutex_init(&mutex, NULL); 
	if (!ret)
	{
		printf ("Creation des threads clients !\n");
		while(i < init->nb_philo)
		{
			ret = pthread_create(&philo[i], NULL, philosophe, &i);
			if (ret)
				ft_printf("OULA1");
			ft_printf("Philo %d !\n", i);
			i++;
		}
		i = 0;
		while (i < init->nb_philo)
		{
			ret = pthread_join(philo[i], NULL);
			if (ret)
				ft_printf("OULA2");
			ft_printf("Philo %d est mort !\n", i);
			i++;
		}
	}
	else
		ft_printf ("OULA3");
}

float	time_diff(struct timeval *start, struct timeval *end)
{
    return ((end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec));
}

/*
void	loopFunc(size_t num)
{
    int tmp = 0;
    for (int i = 0; i < num; ++i) {
        tmp += 1;
    }
}
*/

int	main(int ac, char **av)
{
	t_init	init;
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, NULL);
	//loopFunc(1000000);
	parsing(ac, av, &init);
	create_philo(&init);

	gettimeofday(&end, NULL);
	
    printf("time spent: %0.4f ms\n", time_diff(&start, &end)* 1e3);

	ft_printf("%d ", init.nb_philo);
	ft_printf("%d ", init.time_to_die);
	ft_printf("%d ", init.time_to_eat);
	ft_printf("%d ", init.time_to_sleep);
	ft_printf("%d ", init.nb_must_eat);
	
	ft_printf("\n--------------------------FINIS-------------------------");
	exit(EXIT_SUCCESS);
}