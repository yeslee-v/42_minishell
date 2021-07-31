#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			run_env(int xprt_flag)
{
	t_env		*env_tmp;
	t_process	*proc_lst;
	char		*arg;

	proc_lst = g_sh.process->head;
	arg = proc_lst->cmd->arg;
	env_tmp = g_sh.env->head;
	while (env_tmp)
	{
		if (xprt_flag)
			printf("declare -x %s=\"%s\"\n", env_tmp->key, env_tmp->value);
		else
		{
			if (arg)
			{
				g_sh.exit_status = 127;
				return ;
			}
			else
				printf("%s=%s\n", env_tmp->key, env_tmp->value);
		}
		env_tmp = env_tmp->next;
	}
}
