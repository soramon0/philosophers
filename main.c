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
	int				leftIdx;
	int				rightIdx;
	t_philo			*leftPhilo;
	t_philo			*rightPhilo;

	p = (t_philo *)arg;
	s = p->state;
	if (p->idx % 2 == 0)
	{
		leftIdx = (p->idx - 1 + s->philos_num) % s->philos_num;
		rightIdx = (p->idx + 1) % s->philos_num;
	}
	else
	{
		rightIdx = (p->idx - 1 + s->philos_num) % s->philos_num;
		leftIdx = (p->idx + 1) % s->philos_num;
	}
	leftPhilo = s->philos+ leftIdx;
	rightPhilo = s->philos +rightIdx ;
	dearise(-get_currtime(s->start_time));
	while (1)
	{
		pthread_mutex_lock(&leftPhilo->fork);
		if (is_sim_done(s))
		{
			pthread_mutex_unlock(&leftPhilo->fork);
			break ;
		}
		sim_print(A_FORK_PICK, p);
		pthread_mutex_lock(&rightPhilo->fork);
		if (is_sim_done(s))
		{
			pthread_mutex_unlock(&rightPhilo->fork);
			pthread_mutex_unlock(&leftPhilo->fork);
			break ;
		}
		sim_print(A_FORK_PICK, p);
		pthread_mutex_lock(&p->data_mutex);
		p->last_time_ate = get_currtime(0);
		p->ate_count++;
		if (is_sim_done(s))
		{
			p->ate_count--;
			pthread_mutex_unlock(&p->data_mutex);
			pthread_mutex_unlock(&rightPhilo->fork);
			pthread_mutex_unlock(&leftPhilo->fork);
			break ;
		}
		sim_print(A_EAT, p);
		pthread_mutex_unlock(&p->data_mutex);
		dearise(s->t_eat);
		pthread_mutex_unlock(&rightPhilo->fork);
		pthread_mutex_unlock(&leftPhilo->fork);
		if (is_sim_done(s))
			break ;
		sim_print(A_SLEEP, p);
		dearise(s->t_sleep);
		if (is_sim_done(s))
			break ;
		sim_print(A_THINK, p);
	}
	return (0);
}

void	monitor_philos(t_philo_state *s)
{
	int		i;
	long	last_time;

	while (1)
	{
		i = 0;
		while (i < s->philos_num)
		{
			pthread_mutex_lock(&s->philos[i].data_mutex);
			last_time = get_currtime(s->philos[i].last_time_ate);
			if (last_time > s->t_die)
			{
				pthread_mutex_lock(&s->stop_sim_mutex);
				s->stop_sim = true;
				pthread_mutex_unlock(&s->stop_sim_mutex);
				pthread_mutex_unlock(&s->philos[i].data_mutex);
				sim_print(A_DIED, &s->philos[i]);
				return ;
			}
			pthread_mutex_unlock(&s->philos[i].data_mutex);
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
		if (pthread_create(&s->philos[i].thread, NULL, handler, &s->philos[i]))
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
