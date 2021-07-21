#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			run_unset(char **all_env, t_blt *blt, t_env *env, t_lst *envl)
{
	(void)all_env;
	(void)env;
	if ((blt->up_flag == 1) || !(blt->args))
		return ;
	delete_env_node(blt->args, envl);
}
