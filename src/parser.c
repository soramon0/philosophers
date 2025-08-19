/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_msg(int num, char *label)
{
	if (num <= 0)
	{
		printf("Error: %s should be greater than 0\n", label);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_args(t_philo_state *s, int argc)
{
	if (print_msg(s->t_die, "time_to_die"))
		return (EXIT_FAILURE);
	if (print_msg(s->t_eat, "time_to_eat"))
		return (EXIT_FAILURE);
	if (print_msg(s->t_sleep, "time_to_sleep"))
		return (EXIT_FAILURE);
	if (argc < 6)
		return (EXIT_SUCCESS);
	return (print_msg(s->min_philo_eat,
			"number_of_times_each_philosopher_must_eat"));
}

t_philo_state	*parse_params(int argc, char *argv[])
{
	t_philo_state	*s;
	int				num_philos;

	if (argc < 5 || argc > 6)
		return (printf("Error: invalid args\n"), usage(), NULL);
	num_philos = atoi(argv[1]);
	if (print_msg(num_philos, "number_of_philosophers"))
		return (NULL);
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
	if (check_args(s, argc))
		return (free(s), NULL);
	return (s);
}
