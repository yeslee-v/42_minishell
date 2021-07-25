/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:54:05 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/07/25 14:22:40 by parkjaekw        ###   ########.fr       */
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

void	print_double_str(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		printf("[arg][%d] = %s\n", i, str[i]);
		i++;
	}
}

void	print_cmd(t_cmd *node)
{
	if (!node)
		printf("커맨드가 존재하지 않습니다.\n");
	printf(CYAN"> shell command\n"RESET);
	printf("[cmd] = %s\n[arg] = %s\n\n", node->cmd, node->arg_line);
	print_double_str(node->arg_word);
	printf("-------------------------------\n");
}

void	print_redir(t_process *proc, t_lst *redir)
{
	int i;
	t_redirect *node;

	i = 0;
	node = redir->head;
	if (redir == proc->i_redir)
		printf(RED"> input redirect list\n"RESET);
	else if (redir == proc->o_redir)
		printf(PURPLE"> output redirect list\n"RESET);
	if (!node)
	printf("노드가 없습니다.\n");
	while (node)
	{
		printf("--------------------------------\n");
		printf(YELLOW"(redir node %d)\n"RESET, i);
		printf("[type] = %c\n[arg] = %s\n[fd] = %d\n", node->type, node->arg, node->fd);
		if (node->buffer != NULL)
		{
			printf("input buffer\n");
			print_double_str(node->buffer);
		}
		printf("--------------------------------\n\n");
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
		printf(BLUE"\n[pipe no %d]\n"RESET, i);
		printf("\n");
		print_cmd(tmp->cmd);
		print_redir(tmp, tmp->i_redir);
		print_redir(tmp, tmp->o_redir);
		i++;
		tmp = tmp->next;
	}
}

