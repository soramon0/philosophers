#include "./src/philo.h"

int	main(int argc, char *argv[])
{
	t_philo_params	p;

	memset(&p, 0, sizeof(p));
	if (parse_params(&p, argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	printf("%d %d %d %d [%d]\n", p.num_philos, p.t_die, p.t_eat, p.t_sleep,
		p.num_eats);
	return (EXIT_SUCCESS);
}
