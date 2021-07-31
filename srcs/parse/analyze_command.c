#include "../../includes/minishell.h"
extern t_conf	g_sh;

void	get_redirect_file(t_lst *redir, t_cmd *tmp)
{
	t_redirect *node;

	if (!redir)
		return ;
	node = redir->tail;
	if (node && node->arg)
	{
		if (node->type == 'H')
		{
			tmp->input_redir = make_hdoc_file_name(tmp->i);
			tmp->input_fd = open(tmp->input_redir, O_RDONLY);
		}
		else if (node->type == 'I')
		{
			tmp->input_redir = ft_strdup(node->arg);
			tmp->input_fd = open(tmp->input_redir, O_RDONLY);
		}
		else if (ft_strchr("OA", node->type))
		{
			tmp->output_redir = ft_strdup(node->arg);
			printf("o redir file name = %s\n", tmp->output_redir);
			if (node->type == 'A')
			{
				tmp->append = 1;
				/*tmp->output_fd = open(tmp->output_redir, O_RDWR | O_CREAT | O_APPEND, 0644);*/
			}
			/*else*/
				/*tmp->output_fd = open(tmp->output_redir, O_RDWR | O_CREAT | O_TRUNC, 0644);*/
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

void	analyze_cmd(void)
{
	t_process	*node;

	node = NULL;
	if (!g_sh.process)
		return ;
	node = g_sh.process->head;
	while (node)
	{
		parse_cmd(node, g_sh.env);
		node = node->next;
	}
}
