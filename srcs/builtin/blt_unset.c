#include "../../includes/minishell.h"

extern t_conf	g_sh;

static void	remove_env(char *target, t_env *env)
{
	if (!(ft_strncmp(env->key, target, ft_strlen(env->key)))) // head
	{
		env->next->prev = NULL;
		return ;
	}
	while (env->next) // middle
	{
		if (!(ft_strncmp(env->key, target, ft_strlen(env->key))))
		{
			env->prev->next = env->next;
			env->next->prev = env->prev;
			return ;
		}
		env = env->next;
	}
	if (!(ft_strncmp(env->key, target, ft_strlen(env->key)))) // tail
		env->prev->next = NULL;
	return ;
}

void			run_unset(char **all_env, t_blt *blt, t_env *env)
{
	if ((blt->up_flag == 1) || !(blt->args)) // + run 'unset' alone
		return ;
	while (*all_env)
	{
		if (!(ft_strncmp(*all_env, blt->args, 4)))
			remove_env(blt->args, env);
		all_env++;
	}
}
