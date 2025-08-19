/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_init(t_philo_state *s)
{
	int		i;
	t_philo	*p;

	pthread_mutex_init(&s->print_mutex, NULL);
	pthread_mutex_init(&s->stop_sim_mutex, NULL);
	pthread_mutex_init(&s->philos_ate_mutex, NULL);
	s->stop_sim = false;
	s->philos_ate = 0;
	s->start_time = get_currtime(-10);
	i = 0;
	while (i < s->philos_num)
	{
		p = s->philos + i;
		p->idx = i;
		p->id = i + 1;
		p->state = s;
		p->ate_count = 0;
		p->is_done = false;
		p->last_time_ate = s->start_time;
		pthread_mutex_init(&p->fork, NULL);
		pthread_mutex_init(&p->data_mutex, NULL);
		i++;
	}
}

void	state_cleanup(t_philo_state *s)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < s->philos_num)
	{
		p = s->philos + i;
		pthread_mutex_destroy(&p->fork);
		pthread_mutex_destroy(&p->data_mutex);
		i++;
	}
	pthread_mutex_destroy(&s->print_mutex);
	pthread_mutex_destroy(&s->stop_sim_mutex);
	pthread_mutex_destroy(&s->philos_ate_mutex);
	free(s);
}
