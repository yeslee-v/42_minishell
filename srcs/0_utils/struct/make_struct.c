/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 19:37:36 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 03:01:06 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern t_conf	g_sh;

void	save_process(t_cmd *cmd, t_control *con)
{
	t_process	*tmp;
	t_process	*node;

	node = malloc(sizeof(t_process));
	node->cmd = cmd;
	node->con = con;
	node->redir_err = 0;
	node->next = NULL;
	node->prev = NULL;
	if (g_sh.process->head == NULL && g_sh.process->tail == NULL)
	{
		g_sh.process->head = node;
		g_sh.process->tail = node;
		node->i = 0;
	}
	else if (g_sh.process->head != NULL && g_sh.process->tail != NULL)
	{
		tmp = g_sh.process->tail;
		node->prev = tmp;
		tmp->next = node;
		g_sh.process->tail = node;
		node->i = node->prev->i + 1;
	}
}

void	make_token(t_lst *lst, int st, int ed)
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

void	make_env(t_lst *lst, char *key, char *value)
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
	t_redirect	*node;
	t_redirect	*tmp;

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
