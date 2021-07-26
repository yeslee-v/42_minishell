/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:37:36 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/26 21:02:00 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			save_process(t_cmd *cmd, t_lst *i_redir, t_lst *o_redir)
{
	t_process	*tmp;
	t_process	*node;

	node = malloc(sizeof(t_process));
	node->cmd = cmd;
	node->i_redir = i_redir;
	node->o_redir = o_redir;
	node->next = NULL;
	node->prev = NULL;
	if (g_sh.process->head == NULL && g_sh.process->tail == NULL)
	{
		g_sh.process->head = node;
		g_sh.process->tail = node;
	}
	else if (g_sh.process->head != NULL && g_sh.process->tail != NULL)
	{
		tmp = g_sh.process->tail;
		node->prev = tmp;
		tmp->next = node;
		g_sh.process->tail = node;
	}
}

void			make_token(t_lst *lst, int st, int ed)
{
	t_token	*tmp;
	t_token	*node;

	node = malloc(sizeof(t_token));
	node->token = ft_strrdup(g_sh.cmd, st, ed);
	node->st = st;
	node->ed = ed;
	node->next = NULL;
	node->prev = NULL;
	if (lst->head == NULL && lst->tail == NULL)
	{
		lst->head = node;
		lst->tail = node;
	}
	else if (lst->head != NULL && lst->tail != NULL)
	{
		tmp = lst->tail;
		node->prev = tmp;
		tmp->next = node;
		lst->tail = node;
	}
}

void			make_env(t_lst *lst, char *key, char *value)
{
	t_env	*tmp;
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->next = NULL;
	node->prev = NULL;
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (lst->head == NULL && lst->tail == NULL)
	{
		lst->head = node;
		lst->tail = node;
	}
	else if (lst->head != NULL && lst->tail != NULL)
	{
		tmp = lst->tail;
		node->prev = tmp;
		tmp->next = node;
		lst->tail = node;
	}
}

void	make_redir(t_lst *redir, char type, char *arg)
{
	t_redirect *node;
	t_redirect *tmp;

	node = malloc(sizeof(t_redirect));
	node->type = type;
	node->arg = ft_strdup(arg);
	node->fd = -1;
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
	if (arg)
		free(arg);
}
