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

void	*handler(void *arg)
{
	t_philo			*p;
	t_philo_state	*s;
	int				leftIdx;
	int				rightIdx;
	t_philo			leftPhilo;
	t_philo			rightPhilo;

	p = (t_philo *)arg;
	s = p->state;
	leftIdx = (p->id - 1 + s->philos_num) % s->philos_num;
	rightIdx = (p->id + 1) % s->philos_num;
	leftPhilo = s->philos[leftIdx];
	rightPhilo = s->philos[rightIdx];
	dearise(-get_currtime(s->start_time));
	while (1)
	{
		pthread_mutex_lock(&leftPhilo.fork);
		// // NOTE: clean resources before stopping sim
		pthread_mutex_lock(&s->stop_sim_mutex);
		if (s->stop_sim)
		{
			pthread_mutex_unlock(&s->stop_sim_mutex);
			pthread_mutex_unlock(&leftPhilo.fork);
			break ;
		}
		pthread_mutex_unlock(&s->stop_sim_mutex);
		printf("%ld %d has taken a fork\n", get_currtime(s->start_time), p->id);
		pthread_mutex_lock(&rightPhilo.fork);
		printf("%ld %d has taken a fork\n", get_currtime(s->start_time), p->id);
		pthread_mutex_lock(&p->data_mutex);
		p->last_time_ate = get_currtime(0);
		p->ate_count++;
		printf("%ld %d is eating\n", p->last_time_ate - s->start_time, p->id);
		pthread_mutex_unlock(&p->data_mutex);
		dearise(s->t_eat);
		pthread_mutex_unlock(&rightPhilo.fork);
		pthread_mutex_unlock(&leftPhilo.fork);
		printf("%ld %d is sleeping\n", get_currtime(s->start_time), p->id);
		dearise(s->t_sleep);
		printf("%ld %d is thinking\n", get_currtime(s->start_time), p->id);
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
				printf("%ld %d died\n", get_currtime(s->start_time),
					s->philos[i].id);
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
		if (pthread_create(&s->philos[i].thread, NULL, handler, s->philos + i))
		{
			// TODO(): destory forks
			return (perror("pthread_create"), free(s), EXIT_FAILURE);
		}
		i++;
	}
	monitor_philos(s);
	i = 0;
	while (i < s->philos_num)
	{
		// TODO(): destory forks
		if (pthread_join(s->philos[i++].thread, NULL))
			return (perror("pthread_join"), free(s), EXIT_FAILURE);
	}
	i = 0;
	while (i < s->philos_num)
	{
		pthread_mutex_destroy(&s->philos[i].fork);
		pthread_mutex_destroy(&s->philos[i++].data_mutex);
	}
	return (free(s), EXIT_SUCCESS);
}
