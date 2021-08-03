#include "../../../includes/minishell.h"

void	free_env(t_lst *env)
{
	t_env	*node;
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
		node = tmp;
		tmp = tmp->next;
		free(node);
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

void	free_control(t_control *con)
{
	if (!con)
		return ;
	if (con->redir)
		free_redirect(con->redir);
	if (con->o_redir)
		free_redirect(con->o_redir);
	if (con->i_redir)
		free_redirect(con->i_redir);
	free(con);
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
		remove_hdoc(tmp->i);
		if (tmp->cmd)
			free_cmd(tmp->cmd);
		if (tmp->con)
			free_control(tmp->con);
		node = tmp;
		tmp = tmp->next;
		free(node);
		node = NULL;
	}
	free(process);
}
