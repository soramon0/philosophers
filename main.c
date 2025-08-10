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
	struct timeval	tv;
	long			time;

	p = (t_philo *)arg;
	s = p->state;
	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("gettimeofday error\n");
		return (0);
	}
	time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000.0)) + 0.5;
	printf("%ld %d has taken a fork\n", time, p->id);
	usleep(s->t_sleep);
	printf("%ld %d is eating\n", time, p->id);
	printf("%ld %d is sleeping\n", time, p->id);
	printf("%ld %d is thinking\n", time, p->id);
	printf("%ld %d is dead\n", time, p->id);
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
		if (pthread_create(&s->philos[i].thread, NULL, handler, s->philos + i))
			return (perror("pthread_create"), free(s), EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < s->philos_num)
	{
		if (pthread_join(s->philos[i++].thread, NULL))
			return (perror("pthread_join"), free(s), EXIT_FAILURE);
	}
	return (free(s), EXIT_SUCCESS);
}
