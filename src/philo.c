#include "philo.h"

int	parse_params(t_philo_params *params, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: invalid args\n");
		usage();
		return (EXIT_FAILURE);
	}
	// NOTE: may need extra validation (e.g 100kw -> error | success)
	params->num_philos = atoi(argv[1]);
	params->t_die = atoi(argv[2]);
	params->t_eat = atoi(argv[3]);
	params->t_sleep = atoi(argv[4]);
	if (argc == 6)
		params->num_eats = atoi(argv[5]);
	else
		params->num_eats = -1;
	return (EXIT_SUCCESS);
}
