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

void	philo_state_init(t_philo_state *s)
{
	int	i;

	pthread_mutex_init(&s->stop_sim_mutex, NULL);
	pthread_mutex_init(&s->print_mutex, NULL);
	s->stop_sim = false;
	i = 0;
	while (i < s->philos_num)
	{
		s->philos[i].idx = i;
		s->philos[i].id = i + 1;
		s->philos[i].state = s;
		s->philos[i].ate_count = 0;
		s->philos[i].last_time_ate = s->start_time;
		pthread_mutex_init(&s->philos[i].fork, NULL);
		pthread_mutex_init(&s->philos[i].data_mutex, NULL);
		i++;
	}
}

// NOTE: may need extra validation (e.g 100kw -> error | success)
t_philo_state	*parse_params(int argc, char *argv[])
{
	t_philo_state	*s;
	int				num_philos;

	if (argc < 5 || argc > 6)
		return (printf("Error: invalid args\n"), usage(), NULL);
	num_philos = atoi(argv[1]);
	if (num_philos <= 0)
	{
		printf("Error: number_of_philosophers should be greater than 0\n");
		return (NULL);
	}
	s = malloc(sizeof(t_philo_state) + (num_philos * sizeof(t_philo)));
	if (s == NULL)
		return (NULL);
	s->philos_num = num_philos;
	s->t_die = atoi(argv[2]);
	s->t_eat = atoi(argv[3]);
	s->t_sleep = atoi(argv[4]);
	if (argc == 6)
		s->min_philo_eat = atoi(argv[5]);
	else
		s->min_philo_eat = -1;
	return (s);
}
