#include "../../includes/minishell.h"

extern t_conf g_sh;


/*t_token	*parse_token(t_token *tok, t_lst *syn, char **cmd_t, char **arg_t)*/
/*{*/
	/*char *target;*/

	/*target = NULL;*/
	/*if (tok->type == 'C')*/
		/**cmd_t = ft_strdup(tok->token);*/
	/*else if (tok->type == 'S')*/
		/**arg_t = ft_strjoin_sp(*arg_t, tok->token);*/
	/*else if (tok->type == 'T')*/
		/*target = ft_strdup(tok->token);*/
	/*else if ((ft_strchr("OIAH", tok->type)))*/
	/*{*/
		/*make_syntax(syn, *cmd_t, *arg_t);*/
		/**cmd_t = ft_strdup(tok->token);*/
		/*if (target != NULL)*/
			/*make_syntax(syn, *cmd_t, target);*/
		/**arg_t = NULL;*/
	/*}*/
	/*tok = tok->next;*/
	/*return (tok);*/
/*}*/

void	make_redir(t_lst *redir, char type, char *arg)
{
	t_redirect *node;
	t_redirect *tmp;

	node = malloc(sizeof(t_redirect));
	node->type = type;
	node->arg = ft_strdup(arg);
	node->fd = -1;
	node->buffer = NULL;
	node->prev = NULL;
	node->next = NULL;
	if (redir->head == NULL && redir->tail == NULL)
	{
		redir->head = node;
		redir->tail = node;
	}
	else if (redir->head != NULL && redir->tail != NULL)
	{
		tmp = redir->tail;
		tmp->next = node;
		node->prev = tmp;
		redir->tail = node;
	}
}

void	make_cmd(t_cmd *node, char *cmd, char *arg, char **args)
{
	if (cmd)
		node->cmd = ft_strdup(cmd);
	else
		node->cmd = NULL;
	if (arg)
		node->arg_line = ft_strdup(arg);
	else
		node->arg_line = NULL;
	if (args)
		node->arg_word = args;
	else
		node->arg_word = NULL;
	if (cmd)
		free(cmd);
	cmd = NULL;
	if (arg)
		free(arg);
	arg = NULL;
}

void	init_cmd(t_cmd *node)
{
	node->arg_line = NULL;
	node->arg_word = NULL;
	node->cmd = NULL;
}

int		ft_double_ptrlen(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	**ft_double_strjoin(char **dst, char *src)
{
	char	**ret;
	int size;
	int i;

	i = 0;
	size = 0;
	ret = NULL;
	if (!dst)
	{
		ret = malloc(sizeof(char *) * 2);
		ret[0] = ft_strdup(src);
		ret[1] = NULL;
		return (ret);
	}
	else if (dst)
	{
		size = ft_double_ptrlen(dst);
		ret =  malloc(sizeof(char *) * (size + 2));
		while (dst[i] != NULL)
		{
			ret[i] = ft_strdup(dst[i]);
			i++;
		}
		ret[i] = ft_strdup(src);
		ret[i + 1] = NULL;
		ft_free_double((void **)dst);
		dst = NULL;
		return (ret);
	}
	return (ret);
}

t_token *parser(t_token *tok)
{
	char *cmd;
	char *arg;
	char **args;
	t_lst *i_redir;
	t_lst *o_redir;
	t_cmd *node;

	node = malloc(sizeof(t_cmd));
	i_redir = malloc(sizeof(t_lst));
	o_redir = malloc(sizeof(t_lst));
	args = NULL;
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


/*t_token	*parser(t_lst *process, t_token *tok)*/
/*{*/
	/*char	*cmd_t;*/
	/*char	*arg_t;*/
	/*t_lst	*syn;*/
	/*t_token	*tmp;*/

	/*cmd_t = NULL;*/
	/*arg_t = NULL;*/
	/*tmp = tok;*/
	/*syn = malloc(sizeof(t_lst));*/
	/*init_lst(syn);*/
	/*while (tmp)*/
	/*{*/
		/*if (tmp->i == -1)*/
		/*{*/
			/*tmp = tmp->next;*/
			/*break ;*/
		/*}*/
		/*else*/
			/*tmp = parse_token(tmp, syn, &cmd_t, &arg_t);*/
	/*}*/
	/*if (cmd_t)*/
		/*make_syntax(syn, cmd_t, arg_t);*/
	/*save_process(process, syn);*/
	/*return (tmp);*/
/*}*/
