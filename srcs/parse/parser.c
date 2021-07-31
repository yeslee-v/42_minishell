#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	seperate_redir(t_control *con, char type, char *token)
{
	if (ft_strchr("AO", type))
		make_redir(con->o_redir, type, token);
	else if (ft_strchr("HI", type))
		make_redir(con->i_redir, type, token);
}

t_token	*parse_token(t_token *tok, t_cmd *node, t_control *con)
{
	if (tok->type == 'C')
	{
		node->cmd = ft_strdup(tok->token);
		node->args = ft_double_strjoin(node->args, tok->token);
	}
	else if (tok->type == 'S' && tok->token[0] != '\0')
	{
		node->arg = ft_strcjoin(node->arg, tok->token, ' ');
		node->args = ft_double_strjoin(node->args, tok->token);
	}
	else if (ft_strchr("AOHI", tok->type))
	{
		make_redir(con->redir, tok->type, tok->next->token);
		seperate_redir(con, tok->type, tok->next->token);
	}
	else if (ft_strchr("AO", tok->type))
		make_redir(con->o_redir, tok->type, tok->next->token);
	else if (ft_strchr("HI", tok->type))
		make_redir(con->i_redir, tok->type, tok->next->token);
	return (tok->next);
}

t_token	*parser(t_token *token)
{
	t_control	*con;
	t_token		*tok;
	t_cmd		*node;

	tok = token;
	con = malloc(sizeof(t_control));
	node = malloc(sizeof(t_cmd));
	init_control(con);
	init_cmd(node);
	while (tok)
	{
		tok = parse_token(tok, node, con);
		if (tok && tok->type == 'P')
		{
			save_process(node, con);
			return (tok->next);
		}
	}
	save_process(node, con);
	return (tok);
}
