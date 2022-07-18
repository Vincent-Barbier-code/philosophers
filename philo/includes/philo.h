/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarbier <vbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:55:58 by vbarbier          #+#    #+#             */
/*   Updated: 2022/07/18 02:08:45 by vbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	pthread_mutex_t		m_read;
	pthread_mutex_t		m_die;
	pthread_mutex_t		m_nb_eat;
	pthread_mutex_t		m_state;

}	t_init;

typedef struct s_philo
{
	int					id;
	int					state;
	int					rfork;
	int					lfork;
	pthread_t			thread;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	int					nb_must_eat;
	t_init				*init;

}	t_philo;

//parsing.c
int					parsing(int ac, char **av, t_init *init);

//fork.c
pthread_mutex_t		*init_fork(t_init *init);
void				destroy_fork(t_init *init);
unsigned long int	get_time(void);
void				free_all(t_philo *philo);

//action.c
void				*action(t_philo *philo);

//monitoring.c 
t_philo				*create_monitor(t_philo *philo);
int					join_monitor(t_philo *philo);

//condition.c
int					die(t_philo *philo);
int					init_impair(t_philo *philo);
int					init_pair(t_philo *philo);
int					can_eat(t_philo *philo);
int					can_sleep(t_philo *philo);

#endif
