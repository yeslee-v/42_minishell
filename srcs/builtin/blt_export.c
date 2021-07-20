#include "../../includes/minishell.h"

extern t_conf	g_sh;

static void		add_node_back(char *new_k, char *new_v, t_env *env)
{
	t_env	*new;
	t_env	*env_tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		printf("malloc error in add_node_back");
	env_tmp = env;
	new->key = new_k;
	new->value = new_v;
	while (env_tmp->next)
		env_tmp = env_tmp->next;
	env_tmp->next = new;
}

void			run_export(t_blt *blt, t_env *env)
{
	char	**tmp;
	t_env	*env_tmp;

	if (blt->up_flag == 1)
		return ;
	if (!(blt->args))
	{
		run_env(1, env);
		return ;
	}
	tmp = ft_split(blt->args, '=');
	env_tmp = env;
	while (env_tmp)
	{
		if (!(ft_strncmp(env_tmp->key, tmp[0], 4)))
		{
			env_tmp->value = tmp[1];
			return ;
		}
		env_tmp = env_tmp->next;
	}
	add_node_back(ft_strdup(tmp[0]), ft_strdup(tmp[1]), env);
}
