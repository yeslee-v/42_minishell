#include "../../includes/minishell.h"

void	parse_redir(t_token *tok, t_lst *syn, char **cmd, char **arg)
{
printf("redir arg add = %p\n", *arg);
}

t_lst	*init_syntax(void)
{
	t_lst	*syn;

	syn = malloc(sizeof(t_lst));
	init_lst(syn);
	return (syn);
}

t_token	*parse_token(t_token *tok, t_lst *syn, char **cmd_t, char **arg_t)
{
	if (tok->i == 0 && tok->type == 'S')
		*cmd_t = ft_strdup(tok->token);
	else if (tok->i >= 1 && tok->type == 'S')
	{
		*arg_t = ft_strjoin_sp(*arg_t, tok->token);
	}
	else if (tok->i == 0 && (ft_strchr("OIAH", tok->type)))
	{
		make_syntax(syn, *cmd_t, *arg_t);
		*cmd_t = ft_strdup(tok->token);
		*arg_t = NULL;
	}
	tok = tok->next;
	return (tok);
}

t_token	*parser(t_lst *process, t_token *tok)
{
	char	*cmd_t;
	char	*arg_t;
	t_lst	*syn;
	t_token	*tmp;

	cmd_t = NULL;
	arg_t = NULL;
	tmp = tok;
	syn = malloc(sizeof(t_lst));
	init_lst(syn);
	while (tmp)
	{
		if (tmp->i == -1)
		{
			tmp = tmp->next;
			break ;
		}
		else
			tmp = parse_token(tmp, syn, &cmd_t, &arg_t);
	}
	if (cmd_t)
		make_syntax(syn, cmd_t, arg_t);
	save_process(process, syn);
	return (tmp);
}
