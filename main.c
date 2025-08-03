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

	p = (t_philo *)arg;
	s = p->state;
	printf("%d - philo[%d] will sleep for %dms\n", s->philos_num, p->id,
		s->t_sleep);
	usleep(s->t_sleep);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo_state	*s;
	int				i;

	s = parse_params(argc, argv);
	if (s == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < s->philos_num)
	{
		pthread_create(&s->philos[i].thread, NULL, handler, s->philos + i);
		i++;
	}
	i = 0;
	while (i < s->philos_num)
	{
		pthread_join(s->philos[i++].thread, NULL);
	}
	return (free(s), EXIT_SUCCESS);
}
