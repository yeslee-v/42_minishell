/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:54:05 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/07/29 01:48:29 by parkjaekw        ###   ########.fr       */
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
		printf("|[토큰] = %-18s| ", temp->token);
		printf("|타입 = %c| ", temp->type);
		printf("|순서 = %2d| ", temp->i);
		printf("|시작점 = %3d| |종료점 = %3d|\n", temp->st, temp->ed);
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
	printf(B_YELLOW"> 분할된 커맨드\n"RESET);
	printf(GREEN"  o [cmd] = %s [arg] = %s\n"RESET, node->cmd, node->arg);
	printf(B_RED"> execve() 함수용 커맨드 배열\n"RESET);
	print_double_str(node->args);
	printf(B_CYAN"---------------------------------------\n"RESET);
}

void	print_redir(t_control *con, t_lst *redir)
{
	int i;
	t_redirect *node;

	i = 0;
	node = redir->head;
	if (redir == con->redir)
		printf(B_GREEN"> 전체 리다이렉션 리스트\n"RESET);
	if (redir == con->i_redir)
		printf(B_CYAN"> 입력 리다이렉션 리스트\n"RESET);
	else if (redir == con->o_redir)
		printf(B_BLUE"> 출력 리다이렉션 리스트\n"RESET);
	while (node)
	{
		printf(PURPLE" o (노드 %d) "RESET, i);
		printf("[type] = %c [arg] = %s ", node->type, node->arg);
		printf("[fd] = %d\n", node->fd);
		node = node->next;
		i++;
	}
}

void	print_control(t_control *con)
{
	if (!con->redir->head)
		printf(B_YELLOW"> 리다이렉션이 존재하지 않습니다.\n"RESET);
	else
		print_redir(con, con->redir);
	if (!con->i_redir->head)
		printf(B_CYAN"> 입력 리다이렉션이 존재하지 않습니다.\n"RESET);
	else
		print_redir(con, con->i_redir);
	if (!con->o_redir->head)
		printf(B_BLUE"> 출력 리다이렉션이 존재하지 않습니다.\n"RESET);
	else
		print_redir(con, con->o_redir);
}

void	print_process(t_lst *process)
{
	int			i;
	t_process	*tmp;

	i = 0;
	tmp = process->head;
	printf(B_PURPLE"> 쉘 프롬포트에서 입력받은 커맨드\n"RESET);
	printf(GREEN"  o %s\n"RESET, g_sh.cmd);
	while (tmp)
	{
		printf(CYAN"---------------------------------------------\n"RESET);
		printf(B_BLUE"[파이프 NO. %d]\n"RESET, i);
		print_cmd(tmp->cmd);
		print_control(tmp->con);
		i++;
		tmp = tmp->next;
	}
}
