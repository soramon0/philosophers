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
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo_state	t_philo_state;

typedef enum e_action
{
	A_FORK_PICK,
	A_EAT,
	A_SLEEP,
	A_THINK,
	A_DIED,
}								t_action;

typedef struct s_philo
{
	pthread_mutex_t				data_mutex;
	long						last_time_ate;
	uint						ate_count;

	int							id;
	int							idx;
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
	long						start_time;
	pthread_mutex_t				stop_sim_mutex;
	bool						stop_sim;
	pthread_mutex_t				print_mutex;

	int							philos_num;
	t_philo						philos[];
}								t_philo_state;

void							usage(void);
void							cleanup(t_philo_state *s);

long							get_timestamp(void);
long							get_currtime(long start_time);
void							dearise(long to_arise);
t_philo_state					*parse_params(int argc, char *argv[]);
void							philo_state_init(t_philo_state *s);
bool							is_sim_done(t_philo_state *s);
void							sim_print(t_action action, t_philo *p);

#endif
