#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			run_env(int xprt_flag, t_env *env)
{
	t_env *env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (xprt_flag == 1)
			printf("declare -x %s=\"%s\"\n", env_tmp->key, env_tmp->value);
		else
			printf("%s=%s\n", env_tmp->key, env_tmp->value);
		env_tmp = env_tmp->next;
	}
}
