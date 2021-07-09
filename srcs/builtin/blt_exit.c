#include "../../includes/pipe.h"

void	run_exit(t_all *all)
{
	if (all->parse.up_flag == 1)
		return ;
	printf("exit\n");
	printf("\n");
	exit(0);
}
