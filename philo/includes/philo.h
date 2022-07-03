/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:55:58 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/03 02:28:31 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <pthread.h>
# include <limits.h>
# include "../ft_printf/ft_printf.h"
# include <time.h>
# include <sys/time.h>

# define MIAM 0
# define PENSE 1
# define DORT 2

typedef struct s_init
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_must_eat;
	pthread_mutex_t		*mutex;
}	t_init;

typedef struct s_philo
{
	int					ID;
	int					state;
	int					*fork;
	pthread_t			thread;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	int					nb_must_eat;
	t_init	init;

}	t_philo;

//parsing.c
void	parsing(int ac, char **av, t_init *init);

#endif