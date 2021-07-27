/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:54:05 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/07/27 13:17:53 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	print_token(t_lst *token)
{
	t_token	*temp;

	temp = token->head;
	while (temp)
	{
		printf("token = %s ", temp->token);
		printf("type = %c ", temp->type);
		printf("index = %d ", temp->i);
		printf("st = %d ed = %d ", temp->st, temp->ed);
		printf("next = %p\n", temp->next);
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
	printf(GREEN"[cmd] = %s [arg] = %s\n\n"RESET, node->cmd, node->arg);
	print_double_str(node->args);
	printf("--------------------------------\n");
}

void	print_redir(t_process *proc, t_lst *redir)
{
	int			i;
	t_redirect	*node;

	i = 0;
	node = redir->head;
	if (redir == proc->i_redir)
		printf(RED"> INPUT redirect list\n"RESET);
	else if (redir == proc->o_redir)
		printf(PURPLE"> OUTPUT redirect list\n"RESET);
	if (!node)
		printf("노드가 없습니다.\n");
	while (node)
	{
		printf(YELLOW"(NODE %d) "RESET, i);
		printf("[type] = %c [arg] = %s ", node->type, node->arg);
		printf("[fd] = %d\n", node->fd);
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
	printf("> origin command\n");
	printf(GREEN"%s\n"RESET, g_sh.cmd);
	while (tmp)
	{
		printf(CYAN"---------------------------------------------\n"RESET);
		printf(B_BLUE"[PIPE NO. %d]\n"RESET, i);
		print_cmd(tmp->cmd);
		print_redir(tmp, tmp->i_redir);
		print_redir(tmp, tmp->o_redir);
		i++;
		tmp = tmp->next;
	}
}
