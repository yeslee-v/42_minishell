#include "../../includes/minishell.h"
extern t_conf	g_sh;

void	get_redirect_file(t_lst *redir, t_cmd *tmp)
{
	t_redirect	*node;

	if (!redir)
		return ;
	node = redir->tail;
	if (node && node->arg)
	{
		if (node->type == 'H')
			tmp->input_redir = make_hdoc_file_name(tmp->i);
		else if (node->type == 'I')
			tmp->input_redir = ft_strdup(node->arg);
		else if (ft_strchr("OA", node->type))
		{
			tmp->output_redir = ft_strdup(node->arg);
			if (node->type == 'A')
				tmp->append = 1;
		}
	}
}

void	parse_cmd(t_process *node, t_lst *env)
{
	t_cmd	*tmp;
	int		ret;

	if (!node || !env)
		return ;
	tmp = node->cmd;
	tmp->i = node->i;
	ret = check_cmd_contain_path(tmp);
	if (ret > 0)
		tmp->bin = ft_strdup(tmp->cmd);
	else
		tmp->bin = make_bin_with_path(tmp, env);
	get_redirect_file(node->con->o_redir, tmp);
	get_redirect_file(node->con->i_redir, tmp);
	getcwd(tmp->dir, 2048);
}

void	remove_arg_quote(char **arg)
{
	char	*buf;
	t_lexer	*tmp;

	tmp = lexer(*arg);
	buf = NULL;
	if ((check_quote_exist(tmp->lex)) == 1)
	{
		buf = strdup_only_char(tmp->lex, *arg);
		free(*arg);
		*arg = ft_strdup(buf);
		free(buf);
	}
	free_lexer(tmp);
	tmp = NULL;
}

void	remove_cmd_quote(t_cmd *node)
{
	int	i;

	i = -1;
	if (!node)
		return ;
	if (node->cmd)
		remove_arg_quote(&(node->cmd));
	if (node->arg)
		remove_arg_quote(&(node->arg));
	if (node->args)
	{
		while (node->args[++i])
			remove_arg_quote(&(node->args[i]));
	}
}

void	analyze_command(void)
{
	t_process	*node;
	t_process	*last;

	node = NULL;
	if (!g_sh.process)
		return ;
	node = g_sh.process->head;
	node = g_sh.process->tail;
	while (node)
	{
		remove_cmd_quote(node->cmd);
		parse_cmd(node, g_sh.env);
		node = node->next;
	}
}
