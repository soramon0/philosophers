/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_sim(t_philo_state *s)
{
	pthread_mutex_lock(&s->stop_sim_mutex);
	s->stop_sim = true;
	pthread_mutex_unlock(&s->stop_sim_mutex);
}

void	start_sim(t_philo *p, pthread_mutex_t *fone, pthread_mutex_t *ftwo)
{
	while (!is_sim_done(p->state))
	{
		pthread_mutex_lock(fone);
		sim_print(A_FORK_PICK, p);
		if (p->state->philos_num == 1)
		{
			dearise(p->state->t_die + p->state->t_eat, p->state);
			pthread_mutex_unlock(fone);
			break ;
		}
		pthread_mutex_lock(ftwo);
		sim_print(A_FORK_PICK, p);
		philo_update(p);
		sim_print(A_EAT, p);
		dearise(p->state->t_eat, p->state);
		pthread_mutex_unlock(ftwo);
		pthread_mutex_unlock(fone);
		sim_print(A_SLEEP, p);
		dearise(p->state->t_sleep, p->state);
		sim_print(A_THINK, p);
		if (p->state->philos_num % 2 != 0)
			dearise(p->state->t_eat * 2 - p->state->t_sleep, p->state);
	}
}

pthread_mutex_t	*get_fork(t_philo *p, char direction)
{
	pthread_mutex_t	*fork;

	fork = NULL;
	if (direction == 'r')
	{
		if (p->id % 2 == 0)
			fork = &p->fork;
		else
			fork = &p->state->philos[(p->idx + 1) % p->state->philos_num].fork;
	}
	if (direction == 'l')
	{
		if (p->id % 2 == 0)
			fork = &p->state->philos[(p->idx + 1) % p->state->philos_num].fork;
		else
			fork = &p->fork;
	}
	return (fork);
}
