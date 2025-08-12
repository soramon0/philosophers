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
#include <pthread.h>

static void	philos_init(t_philo_state *s)
{
	int	i;

	i = 0;
	while (i < s->philos_num)
	{
		s->philos[i].id = i;
		s->philos[i].state = s;
		pthread_mutex_init(&s->philos[i].fork, NULL);
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
	return (philos_init(s), s);
}
