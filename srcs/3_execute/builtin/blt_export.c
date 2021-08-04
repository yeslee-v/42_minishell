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

char	**split_args(char *b_args, t_cmd *proc)
{
	int		i;
	char	**tmp;

	tmp = NULL;
	i = -1;
	while (b_args[++i])
		if (b_args[i] == '=')
			break ;
	if (i == 0)
	{
		g_sh.exit_status = 1;
		printf("%s: %s: `%s': %s\n", BS, proc->cmd, b_args, NVI);
		return (NULL);
	}
	tmp = malloc(sizeof(char *) * 3);
	tmp[2] = NULL;
	tmp[0] = ft_strrdup(b_args, 0, (i - 1));
	tmp[1] = ft_strrdup(b_args, (i + 1), (ft_strlen(b_args)) - 1);
	return (tmp);
}

void	do_export(int i, char *b_args, t_cmd *proc)
{
	char	**tmp;
	t_env	*xst_key;

	tmp = NULL;
	(void)i;
	if (!(ft_strchr(b_args, '=')))
	{
		check_args(b_args, proc);
		return ;
	}
	tmp = split_args(b_args, proc);
	if (!tmp)
		return ;
	if (check_args(tmp[0], proc))
	{
		ft_free_double((void **)tmp);
		return ;
	}
	xst_key = change_env_value(tmp[0], tmp[1], g_sh.env);
	if (!xst_key)
		add_node_back(ft_strdup(tmp[0]), ft_strdup(tmp[1]));
	ft_free_double((void **)tmp);
	return ;
}

void	run_export(t_cmd *proc, t_blt *blt)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	if (blt->up_flag == 1)
		return ;
	if (!(proc->arg))
	{
		run_env(1, proc);
		return ;
	}
	i = 0;
	if (ft_strchr(proc->arg, ' '))
	{
		tmp = ft_split(proc->arg, ' ');
		while (tmp[i])
		{
			do_export(i, tmp[i], proc);
			i++;
		}
		ft_free_double((void **)tmp);
		return ;
	}
	do_export(i, proc->arg, proc);
}
