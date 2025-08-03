#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_philo_params
{
	int	num_philos;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	num_eats;
}		t_philo_params;

void	usage(void);
int		parse_params(t_philo_params *params, int argc, char *argv[]);
