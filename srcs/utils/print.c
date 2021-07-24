/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:54:05 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/07/24 18:19:36 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf g_sh;

void	print_system(void)
{
	printf("[lexical analysis]\n");
	printf("cmd = %s\nlex = %s\n", g_sh.cmd, g_sh.lexer->lex);
	printf("------------------\n");
	printf("[tokenizing]\n");
	print_token(g_sh.token);
	printf("------------------\n");
	printf("[parsing]\n");
	print_process(g_sh.process);
	printf("------------------\n");
}

void	print_token(t_lst *token)
{
	t_token	*temp;

	temp = token->head;
	while (temp)
	{
		printf("token = %s, type = %c, index = %d, st = %d, ed = %d, next = "
				"%p\n",
				temp->token,
				temp->type,
				temp->i,
				temp->st,
				temp->ed,
				temp->next);
		temp = temp->next;
	}
}

void	print_env(t_lst *env)
{
	t_env	*tmp;

	tmp = env->head;
	while (tmp)
	{
		printf("==============================\n");
		printf("key = %s\nvalue = %s\n", tmp->key, tmp->value);
		printf("==============================\n");
		tmp = tmp->next;
	}
}

void	print_cmd(t_cmd *node)
{
	if (!node)
		printf("커맨드가 존재하지 않습니다.\n");
	printf("> shell command\n");
	printf("[cmd] = %s\n[arg] = %s\n\n", node->cmd, node->arg_line);
}

void	print_redir(t_lst *redir)
{
	int i;
	t_redir *node;

	i = 0;
	node = redir->head;
	printf("> redirect list\n");
	if (!node)
	printf("노드가 없습니다.\n");
	while (node)
	{
		printf("(redir node %d)\n", i);
		printf("[type] = %c\n[target_file_name] = %s\n[from_fd] = %d\n\n", node->type, node->file, node->pre_fd);
		node = node->next;
		i++;
	}
}

void	print_hdoc(t_lst *hdoc)
{
	int i;
	t_hdoc *node;

	i = 0;
	node = hdoc->head;
	printf("> hdoc list\n");
	if (!node)
		printf("노드가 없습니다.\n");
	while (node)
	while (node)
	{
		printf("(hdoc node %d)\n", i);
		printf("[delimiter] = %s\n[pre_fd] = %d\n\n", node->delimiter, node->pre_fd);
		node = node->next;
		i++;
	}
}

void	print_process(t_lst *process)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = process->head;
	printf("> origin command");
	printf("%s\n\n", g_sh.cmd);
	while (tmp)
	{
		printf("\n[pipe no %d]\n", i);
		printf("-------------------------\n");
		printf("\n");
		print_cmd(tmp->cmd);
		print_redir(tmp->redir);
		print_hdoc(tmp->hdoc);
		i++;
		tmp = tmp->next;
	}
}

