#include "../../includes/minishell.h"

extern t_conf	g_sh;

t_token			*parser(t_token *tok)
{
	char	*cmd;
	char	*arg;
	char	**args;
	t_lst	*i_redir;
	t_lst	*o_redir;
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	i_redir = malloc(sizeof(t_lst));
	o_redir = malloc(sizeof(t_lst));
	arg = NULL;
	init_lst(o_redir);
	init_cmd(node);
	init_lst(i_redir);
	cmd = NULL;
	arg = NULL;
	while (tok)
	{
		if (tok->type == 'C')
		{
			cmd = ft_strdup(tok->token);
			args = ft_double_strjoin(args, tok->token);
		}
		else if (tok->type == 'S')
		{
			arg = ft_strjoin_sp(arg, tok->token);
			args = ft_double_strjoin(args, tok->token);
		}
		else if (ft_strchr("AO", tok->type))
			make_redir(o_redir, tok->type, tok->next->token);
		else if (ft_strchr("HI", tok->type))
			make_redir(i_redir, tok->type, tok->next->token);
		else if (tok->type == 'P')
		{
			make_cmd(node, cmd, arg, args);
			save_process(node, i_redir, o_redir);
			return (tok->next);
		}
		tok = tok->next;
	}
	if (cmd != NULL)
		make_cmd(node, cmd, arg, args);
	save_process(node, i_redir, o_redir);
	return (tok);
}
