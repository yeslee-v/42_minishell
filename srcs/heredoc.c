#include "../includes/pipe.h"

int	main(int ac, char **av)
{
	int i;

	if (ac != 4)
		printf("invalid ac\n");
	i = -1;
	while (av[++i])
		printf("%s\n", av[i]);
	return (0);
}
