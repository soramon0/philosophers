/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_sim_done(t_philo_state *s)
{
	pthread_mutex_lock(&s->stop_sim_mutex);
	if (s->stop_sim)
	{
		pthread_mutex_unlock(&s->stop_sim_mutex);
		return (true);
	}
	pthread_mutex_unlock(&s->stop_sim_mutex);
	return (false);
}

void	sim_print(t_action action, t_philo *p)
{
	long	time;

	if (pthread_mutex_lock(&p->state->print_mutex))
	{
		perror("pthread_mutex_lock print_mutex");
		return ;
	}
	time = get_currtime(p->state->start_time);
	if (action == A_FORK_PICK)
		printf("%ld %d has taken a fork\n", time, p->id);
	if (action == A_EAT)
	{
		time = p->last_time_ate - p->state->start_time;
		printf("%ld %d is eating\n", time, p->id);
	}
	if (action == A_SLEEP)
		printf("%ld %d is sleeping\n", time, p->id);
	if (action == A_THINK)
		printf("%ld %d is thinking\n", time, p->id);
	if (action == A_DIED)
		printf("%ld %d died\n", time, p->id);
	if (pthread_mutex_unlock(&p->state->print_mutex))
	{
		perror("pthread_mutex_unlock print_mutex");
		return ;
	}
}
