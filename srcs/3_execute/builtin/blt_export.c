#include "../../../includes/minishell.h"

extern t_conf	g_sh;

static void	add_node_back(char *new_k, char *new_v)
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

char	**split_args(char *b_args)
{
	char	**tmp;
	int		i;

	if (!(ft_isalpha(b_args[0]) || (b_args[0] == '_')))
	{
		g_sh.exit_status = 1;
		return (NULL);
	}
	i = -1;
	while (b_args[++i])
	{
		if (b_args[i] == '=')
			break ;
	}
	if (i == 0)
	{
		g_sh.exit_status = 1;
		return (NULL);
	}
	tmp = malloc(sizeof(char *) * 3);
	tmp[2] = NULL;
	b_args[i] = '\0';
	tmp[0] = ft_strdup(b_args);
	tmp[1] = ft_strdup(&b_args[i + 1]);
	return (tmp);
}

void	do_export(int i, char *b_args)
{
	char	**tmp;
	t_env	*xst_key;

	tmp = NULL;
	if (!(ft_strchr(b_args, '=')))
	{
		if (i != 0)
			return ;
		if (!(ft_isalpha(b_args[0]) || (b_args[0] == '_')))
			g_sh.exit_status = 1;
		return ;
	}
	tmp = split_args(b_args);
	if (!tmp)
		return ;
	xst_key = change_env_value(tmp[0], tmp[1], g_sh.env);
	if (!xst_key)
		add_node_back(ft_strdup(tmp[0]), ft_strdup(tmp[1]));
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
}

void	run_export(char *b_args, t_blt *blt)
{
	char	**tmp;
	t_cmd	*proc;
	int		i;

	proc = NULL;
	tmp = NULL;
	if (blt->up_flag == 1)
		return ;
	if (!(b_args))
	{
		run_env(1);
		return ;
	}
	i = 0;
	if (ft_strchr(b_args, ' '))
	{
		tmp = ft_split(b_args, ' ');
		while (tmp[i])
		{
			do_export(i, tmp[i]);
			i++;
		}
		return ;
	}
	do_export(i, b_args);
}
