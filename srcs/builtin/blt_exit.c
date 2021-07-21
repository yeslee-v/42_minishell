#include "../../includes/minishell.h"

void	run_exit(t_blt *blt)
{
	if (blt->up_flag == 1)
		return ;
	printf("exit\n");
	printf("\n");
	exit(0);
}
