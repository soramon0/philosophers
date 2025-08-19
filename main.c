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
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	p = (t_philo *)arg;
	first_fork = get_fork(p, 'l');
	second_fork = get_fork(p, 'r');
	dearise(-get_currtime(p->state->start_time), NULL);
	start_sim(p, first_fork, second_fork);
	return (0);
}

void	monitor_philos(t_philo_state *s)
{
	int		i;
	t_philo	*p;

	while (1)
	{
		i = 0;
		while (i < s->philos_num)
		{
			p = s->philos + i;
			pthread_mutex_lock(&p->data_mutex);
			if (all_philo_done_eating(p))
			{
				pthread_mutex_unlock(&p->data_mutex);
				return ;
			}
			if (is_philo_dead(p))
			{
				pthread_mutex_unlock(&p->data_mutex);
				return ;
			}
			pthread_mutex_unlock(&p->data_mutex);
			i++;
		}
	}
}

int	create_philos(t_philo_state *s)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < s->philos_num)
	{
		p = s->philos + i;
		if (pthread_create(&p->thread, NULL, handler, p))
		{
			printf("pthread_create failed\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	join_philos(t_philo_state *s)
{
	int		i;
	t_philo	*p;

	i = 0;
	while (i < s->philos_num)
	{
		p = s->philos + i;
		if (pthread_join(p->thread, NULL))
		{
			printf("pthread_join failed\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_philo_state	*s;

	s = parse_params(argc, argv);
	if (s == NULL)
		return (EXIT_FAILURE);
	state_init(s);
	if (create_philos(s))
		return (state_cleanup(s), EXIT_FAILURE);
	monitor_philos(s);
	if (join_philos(s))
		return (state_cleanup(s), EXIT_FAILURE);
	return (state_cleanup(s), EXIT_SUCCESS);
}
