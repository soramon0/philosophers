/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klaayoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:18:11 by klaayoun          #+#    #+#             */
/*   Updated: 2024/10/25 22:21:05 by klaayoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(void)
{
	printf("Usage:\n");
	printf("\t./philosophers ");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
}

void	cleanup(t_philo_state *s)
{
	int	i;

	i = 0;
	while (i < s->philos_num)
	{
		pthread_mutex_destroy(&s->philos[i].fork);
		pthread_mutex_destroy(&s->philos[i].data_mutex);
		i++;
	}
	pthread_mutex_destroy(&s->print_mutex);
	pthread_mutex_destroy(&s->stop_sim_mutex);
	free(s);
}

long	get_timestamp(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) != 0)
	{
		printf("gettimeofday error\n");
		return (-1);
	}
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long	get_currtime(long start_time)
{
	return (get_timestamp() - start_time);
}

void	dearise(long to_arise)
{
	long	end;
	long	time_slot;

	end = get_currtime(-to_arise);
	time_slot = to_arise * 0.8;
	usleep(time_slot);
	while (get_currtime(end) < 0)
		usleep(100);
}
