#include "../../../includes/minishell.h"

extern t_conf	g_sh;

void	run_unset(char *b_args, t_blt *blt)
{
	if ((blt->up_flag == 1) || !(b_args))
		return ;
	delete_env_node(b_args, g_sh.env);
}
