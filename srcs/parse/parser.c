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

void	make_redir(t_lst *redir, char type, char *file, char *fd)
{
	t_redir *node;
	t_redir *tmp;

	node = malloc(sizeof(t_redir));
	node->type = type;
	node->file = file;
	node->pre_fd = ft_atoi(fd);
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

void	make_hdoc(t_lst *hdoc, char *delimiter, char *fd)
{
	t_hdoc *node;
	t_hdoc *tmp;

	node = malloc(sizeof(t_hdoc));
	node->delimiter = ft_strdup(delimiter);
	node->pre_fd = ft_atoi(fd);
	node->next = NULL;
	node->prev = NULL;
	if (hdoc->head == NULL && hdoc->tail == NULL)
	{
		hdoc->head = node;
		hdoc->tail = node;
	}
	else if (hdoc->head != NULL && hdoc->tail != NULL)
	{
		tmp = hdoc->tail;
		tmp->next = node;
		node->prev = tmp;
		hdoc->tail = node;
	}
}

void	make_cmd(t_cmd *node, char *cmd, char *arg)
{
	if (cmd)
		node->cmd = ft_strdup(cmd);
	else
		node->cmd = NULL;
	if (arg)
		node->arg_line = ft_strdup(arg);
	else
		node->arg_word = NULL;
	if (cmd)
		free(cmd);
	if (arg)
		free(arg);
}

void	init_cmd(t_cmd *node)
{
	node->arg_line = NULL;
	node->arg_word = NULL;
	node->cmd = NULL;
}

t_token *parser(t_token *tok)
{
	char *cmd;
	char *arg;
	t_lst *redir;
	t_lst *hdoc;
	t_cmd *node;

	node = malloc(sizeof(t_cmd));
	redir = malloc(sizeof(t_lst));
	hdoc = malloc(sizeof(t_lst));
	init_lst(redir);
	init_cmd(node);
	init_lst(hdoc);
	cmd = NULL;
	arg = NULL;
	while (tok)
	{
		if (tok->type == 'C')
			cmd = ft_strdup(tok->token);
		else if (tok->type == 'S')
			arg = ft_strjoin_sp(arg, tok->token);
		else if (ft_strchr("AIO", tok->type))
		{
			printf("redir parse\n");
			if (tok->prev != NULL && tok->prev->type == 'F')
				make_redir(redir, tok->type, tok->next->token, tok->prev->token);
			else
				make_redir(redir, tok->type, tok->next->token, "1");
		}
		else if (tok->type == 'H')
		{
			printf("parse hdoc\n");
			if(tok->prev != NULL && tok->prev->type == 'F')
				make_hdoc(hdoc, tok->next->token, tok->prev->token);
			else
				make_hdoc(hdoc, tok->next->token, "0");
		}
		else if (tok->type == 'P')
		{
			make_cmd(node, cmd, arg);
			save_process(node, redir, hdoc);
			return (tok->next);
		}
		tok = tok->next;
	}
	if (cmd != NULL)
		make_cmd(node, cmd, arg);
	save_process(node, redir, hdoc);
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
