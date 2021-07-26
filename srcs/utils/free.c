#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			free_conf(t_conf *conf)
{
	if (!conf)
		return ;
	if (conf->cmd)
		free(conf->cmd);
	if (conf->lexer)
		free_lexer(conf->lexer);
	if (conf->token)
		free_token(conf->token);
	if (conf->process)
		free_process(conf->process);
}

void			free_env(t_lst *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	tmp = env->head;
	while (tmp)
	{
		if (tmp->key != NULL)
			free(tmp->key);
		if (tmp->value != NULL)
			free(tmp->value);
		tmp = tmp->next;
	}
	free(env);
}

void			free_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	else if (lexer->lex != NULL)
		free(lexer->lex);
	free(lexer);
}

void			free_token(t_lst *token)
{
	t_token	*node;
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token->tail;
	while (tmp)
	{
		node = tmp;
		tmp = tmp->prev;
		if (node)
		{
			if (node->token)
				free(node->token);
			free(node);
		}
	}
	free(token);
}

void	free_cmd(t_cmd *node)
{
	if (!node)
		return ;
	if (node->cmd)
		free(node->cmd);
	if (node->arg_line)
		free(node->arg_line);
	if (node->arg_word)
		ft_free_double((void **)node->arg_word);
	free(node);
}

void	free_redirect(t_lst *redir)
{
	t_redirect *node;
	t_redirect *tmp;

	node = redir->head;
	while (node)
	{
		if (node->arg)
			free(node->arg);
		tmp = node;
		node = node->next;
		free(tmp);
		tmp = NULL;
	}
	free(redir);
}

void			free_process(t_lst *process)
{
	t_process	*node;
	t_process	*tmp;

	if (!process)
		return ;
	tmp = process->head;
	while (tmp)
	{
		if (tmp->cmd)
			free_cmd(tmp->cmd);
		if (tmp->i_redir)
			free_redirect(tmp->i_redir);
		if (tmp->o_redir)
			free_redirect(tmp->o_redir);
		node = tmp;
		tmp = tmp->next;
		free(node);
		node = NULL;
	}
	free(process);
}
