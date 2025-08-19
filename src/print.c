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
	bool	val;

	pthread_mutex_lock(&s->stop_sim_mutex);
	val = s->stop_sim;
	pthread_mutex_unlock(&s->stop_sim_mutex);
	return (val);
}

bool	is_philo_done(t_philo *p)
{
	bool	val;

	pthread_mutex_lock(&p->data_mutex);
	val = p->is_done;
	pthread_mutex_unlock(&p->data_mutex);
	return (val);
}

void	sim_print(t_action action, t_philo *p)
{
	long	time;

	if (is_sim_done(p->state) || is_philo_done(p))
		return ;
	pthread_mutex_lock(&p->state->print_mutex);
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
	pthread_mutex_unlock(&p->state->print_mutex);
}
