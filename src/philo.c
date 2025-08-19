/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_update(t_philo *p)
{
	pthread_mutex_lock(&p->data_mutex);
	p->last_time_ate = get_currtime(0);
	if (p->state->min_philo_eat != -1)
	{
		p->ate_count++;
		if (p->ate_count >= p->state->min_philo_eat)
		{
			pthread_mutex_lock(&p->state->philos_ate_mutex);
			p->state->philos_ate++;
			pthread_mutex_unlock(&p->state->philos_ate_mutex);
		}
	}
	pthread_mutex_unlock(&p->data_mutex);
}

bool	all_philo_done_eating(t_philo *p)
{
	if (p->state->min_philo_eat == -1)
		return (false);
	pthread_mutex_lock(&p->state->philos_ate_mutex);
	if (p->state->philos_ate >= p->state->philos_num)
	{
		finish_sim(p->state);
		p->is_done = true;
		pthread_mutex_unlock(&p->state->philos_ate_mutex);
		return (true);
	}
	pthread_mutex_unlock(&p->state->philos_ate_mutex);
	return (false);
}

bool	is_philo_dead(t_philo *p)
{
	if (get_currtime(p->last_time_ate) > p->state->t_die)
	{
		p->is_done = true;
		finish_sim(p->state);
		pthread_mutex_lock(&p->state->print_mutex);
		printf("%ld %d died\n", get_currtime(p->state->start_time), p->id);
		pthread_mutex_unlock(&p->state->print_mutex);
		return (true);
	}
	return (false);
}
