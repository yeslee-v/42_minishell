#include "../../includes/minishell.h"

extern t_conf	g_sh;

static void		add_node_back(char *new_k, char *new_v)
{
	t_env	*node;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		printf("malloc error in add_node_back");
	node = g_sh.env->tail;
	new->key = new_k;
	new->value = new_v;
	new->next = NULL;
	new->prev = node;
	node->next = new;
	g_sh.env->tail = new;
}

void			run_export(char *b_args, t_blt *blt)
{
	t_cmd *proc;
	char	**tmp;
	t_env	*xst_key;

	proc = NULL;
	if (blt->up_flag == 1)
		return ;
	if (!(b_args))
	{
		run_env(1);
		return ;
	}
	tmp = ft_split(b_args, '=');
	xst_key = change_env_value(tmp[0], tmp[1], g_sh.env);
	if (!xst_key)
		add_node_back(ft_strdup(tmp[0]), ft_strdup(tmp[1]));
}
