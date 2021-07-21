#include "../../includes/minishell.h"

extern t_conf	g_sh;

static void		add_node_back(char *new_k, char *new_v, t_lst *envl)
{
	t_env	*node;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		printf("malloc error in add_node_back");
	node = envl->tail;
	new->key = new_k;
	new->value = new_v;
	new->next = NULL;
	new->prev = node;
	node->next = new;
	envl->tail = new;
}

void			run_export(t_blt *blt, t_lst *envl)
{
	char	**tmp;
	t_env	*xst_key;

	if (blt->up_flag == 1)
		return ;
	if (!(blt->args))
	{
		run_env(1, envl);
		return ;
	}
	tmp = ft_split(blt->args, '=');
	xst_key = change_env_value(tmp[0], tmp[1], envl);
	if (!xst_key)
		add_node_back(ft_strdup(tmp[0]), ft_strdup(tmp[1]), envl);
}
