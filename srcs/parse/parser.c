#include "../../includes/minishell.h"

extern t_conf	g_sh;

t_token	*parse_token(t_token *tok, t_cmd *node, t_lst *i_redir, t_lst *o_redir)
{
	if (tok->type == 'C')
	{
		node->cmd = ft_strdup(tok->token);
		node->args = ft_double_strjoin(node->args, tok->token);
	}
	else if (tok->type == 'S')
	{
		node->arg = ft_strcjoin(node->arg, tok->token, ' ');
		node->args = ft_double_strjoin(node->args, tok->token);
	}
	else if (ft_strchr("AO", tok->type))
		make_redir(o_redir, tok->type, tok->next->token);
	else if (ft_strchr("HI", tok->type))
		make_redir(i_redir, tok->type, tok->next->token);
	return (tok->next);
}

t_token	*parser(t_token *token)
{
	t_lst	*i_redir;
	t_lst	*o_redir;
	t_token	*tok;
	t_cmd	*node;

	tok = token;
	node = malloc(sizeof(t_cmd));
	i_redir = malloc(sizeof(t_lst));
	o_redir = malloc(sizeof(t_lst));
	init_lst(o_redir);
	init_cmd(node);
	init_lst(i_redir);
	while (tok)
	{
		tok = parse_token(tok, node, i_redir, o_redir);
		if (tok && tok->type == 'P')
		{
			save_process(node, i_redir, o_redir);
			return (tok->next);
		}
	}
	save_process(node, i_redir, o_redir);
	return (tok);
}
