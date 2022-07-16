/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:55:58 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/16 20:22:20 by vbarbier         ###   ########.fr       */
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
# define DIE 3

typedef struct s_init
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	unsigned long int	time;
	int					die;
	pthread_mutex_t		*fork;
	pthread_t			monitor_time_die;
	pthread_mutex_t		read;
	pthread_mutex_t		pense;
	pthread_mutex_t		m_die;
	pthread_mutex_t		m_nb_eat;
}	t_init;

typedef struct s_philo
{
	int					ID;
	int					state;
	int					rfork;
	int					lfork;
	pthread_t			thread;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	int					nb_must_eat;
	t_init				init;

}	t_philo;

//parsing.c
void	parsing(int ac, char **av, t_init *init);

//fork.c
pthread_mutex_t	*init_fork(t_init *init);
void	destroy_fork(t_init *init);
unsigned long int	get_time(void);

//action.c
void	*action(t_philo *philo);

//monitoring.c 
t_philo	*create_monitor(t_philo *philo);
int	join_monitor(t_philo *philo);


#endif
