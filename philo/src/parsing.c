/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:54:09 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/07 00:52:27 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	error()
{
	ft_putstr_fd("Error : Mauvais arguments \n", 2);
	exit(EXIT_FAILURE);	
}

static int	ft_atoi(char *str)
{
	int			i;
	int			signe;
	long int	nb;

	signe = 1;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	nb = signe * nb;
	if (nb > INT_MAX || nb < INT_MIN)
		error();
	return (nb);
}

static void	verif_nb(int ac, char **av)
{
	int	x;
	int y;

	x = 0;
	y = 1;		
	while (y < ac)
	{
		x = 0;
		while (av[y][x])
		{
			if (av[y][x] < '0' || av[y][x] > '9')
				error();
			x++;
		}
		y++;
	}
}

void	parsing(int ac, char **av, t_init *init)
{
	init->nb_must_eat = 0;
	if (ac > 6 || ac < 5)
		error();
	verif_nb(ac, av);
	init->nb_philo = ft_atoi(av[1]);
	init->time_to_die = ft_atoi(av[2]);
	init->time_to_eat = ft_atoi(av[3]);
	init->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		init->nb_must_eat = ft_atoi(av[5]);
	else
		init->nb_must_eat = 0;
}
