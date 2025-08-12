/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_state	t_philo_state;

typedef struct s_philo
{
	int							id;
	pthread_t					thread;
	pthread_mutex_t				fork;
	t_philo_state				*state;
}								t_philo;

typedef struct s_philo_state
{
	int							t_die;
	int							t_eat;
	int							t_sleep;
	int							min_philo_eat;

	int							philos_num;
	t_philo						philos[];
}								t_philo_state;

void							usage(void);
t_philo_state					*parse_params(int argc, char *argv[]);

#endif
