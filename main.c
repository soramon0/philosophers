/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./src/philo.h"

void	*handler(void *arg)
{
	t_philo			*p;
	t_philo_state	*s;
	int				lidx;
	int				ridx;
	t_philo			lphilo;
	t_philo			rphilo;

	p = (t_philo *)arg;
	s = p->state;
	lidx = (p->id - 1 + s->philos_num) % s->philos_num;
	ridx = (p->id + 1) % s->philos_num;
	lphilo = s->philos[lidx];
	rphilo = s->philos[ridx];
	dearise(-get_currtime(s->start_time));
	while (1)
	{
		pthread_mutex_lock(&lphilo.fork);
		// // NOTE: clean resources before stopping sim
		pthread_mutex_lock(&s->stop_sim_mutex);
		if (s->stop_sim)
		{
			pthread_mutex_unlock(&s->stop_sim_mutex);
			pthread_mutex_unlock(&lphilo.fork);
			break ;
		}
		pthread_mutex_unlock(&s->stop_sim_mutex);
		printf("%ld %d has taken a fork\n", get_currtime(s->start_time), p->id);
		pthread_mutex_lock(&rphilo.fork);
		printf("%ld %d has taken a fork\n", get_currtime(s->start_time), p->id);
		pthread_mutex_lock(&p->data_mutex);
		p->last_time_ate = get_currtime(0);
		p->ate_count++;
		printf("%ld %d is eating\n", p->last_time_ate - s->start_time, p->id);
		pthread_mutex_unlock(&p->data_mutex);
		dearise(s->t_eat);
		pthread_mutex_unlock(&rphilo.fork);
		pthread_mutex_unlock(&lphilo.fork);
		printf("%ld %d is sleeping\n", get_currtime(s->start_time), p->id);
		dearise(s->t_sleep);
		printf("%ld %d is thinking\n", get_currtime(s->start_time), p->id);
	}
	return (0);
}

void	monitor_philos(t_philo_state *s)
{
	int		i;
	t_philo	p;

	while (1)
	{
		i = 0;
		while (i < s->philos_num)
		{
			p = s->philos[i];
			pthread_mutex_lock(&p.data_mutex);
			if (get_currtime(p.last_time_ate) > s->t_die)
			{
				pthread_mutex_lock(&s->stop_sim_mutex);
				s->stop_sim = true;
				pthread_mutex_unlock(&s->stop_sim_mutex);
				pthread_mutex_unlock(&p.data_mutex);
				printf("%ld %d died\n", get_currtime(s->start_time), p.id);
				return ;
			}
			pthread_mutex_unlock(&p.data_mutex);
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	t_philo_state	*s;
	int				i;

	s = parse_params(argc, argv);
	if (s == NULL)
		return (EXIT_FAILURE);
	s->start_time = get_currtime(-1);
	philo_state_init(s);
	i = 0;
	while (i < s->philos_num)
	{
		if (pthread_create(&s->philos[i].thread, NULL, handler, s->philos + i))
		{
			printf("pthread_create failed\n");
			return (cleanup(s), EXIT_FAILURE);
		}
		i++;
	}
	monitor_philos(s);
	i = 0;
	while (i < s->philos_num)
	{
		if (pthread_join(s->philos[i++].thread, NULL))
			return (printf("pthread_join failed\n"), cleanup(s), EXIT_FAILURE);
	}
	return (cleanup(s), EXIT_SUCCESS);
}
