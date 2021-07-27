#include "../../includes/minishell.h"

void	free_env(t_lst *env)
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

void	free_redirect(t_lst *redir)
{
	t_redirect	*node;
	t_redirect	*tmp;

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

void	free_token(t_lst *token)
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

void	free_process(t_lst *process)
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
