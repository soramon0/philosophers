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

int	print_overflow(char *src, int *num, char *label)
{
	if (ft_atoi(src, num))
	{
		printf("Error: %s cannot be contained inside of an int\n", label);
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

int	parse_ints(t_philo_state *s, char **argv, int argc)
{
	char	*label;

	if (print_overflow(argv[2], &s->t_die, "time_to_die"))
		return (EXIT_FAILURE);
	if (print_overflow(argv[3], &s->t_eat, "time_to_eat"))
		return (EXIT_FAILURE);
	if (print_overflow(argv[4], &s->t_sleep, "time_to_sleep"))
		return (EXIT_FAILURE);
	if (argc == 6)
	{
		label = "number_of_times_each_philosopher_must_eat";
		if (print_overflow(argv[5], &s->min_philo_eat, label))
			return (EXIT_FAILURE);
	}
	else
		s->min_philo_eat = -1;
	return (EXIT_SUCCESS);
}

t_philo_state	*parse_params(int argc, char *argv[])
{
	t_philo_state	*s;
	int				num_philos;

	num_philos = 0;
	if (argc < 5 || argc > 6)
		return (printf("Error: invalid args\n"), usage(), NULL);
	if (ft_atoi(argv[1], &num_philos))
	{
		printf("Error: number_of_philosophers cannot be");
		printf("contained inside of an int\n");
		return (NULL);
	}
	if (print_msg(num_philos, "number_of_philosophers"))
		return (NULL);
	s = malloc(sizeof(t_philo_state) + (num_philos * sizeof(t_philo)));
	if (s == NULL)
		return (NULL);
	s->philos_num = num_philos;
	if (parse_ints(s, argv, argc))
		return (free(s), NULL);
	if (check_args(s, argc))
		return (free(s), NULL);
	return (s);
}
