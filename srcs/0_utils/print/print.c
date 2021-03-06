/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 18:54:05 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/08/03 04:30:21 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern t_conf	g_sh;

void	print_cmd(t_cmd *node)
{
	if (!node)
		printf("커맨드가 존재하지 않습니다.\n");
	printf(B_PURPLE"> 분할된 커맨드\n"RESET);
	printf(GREEN"  o [cmd] = [%s] [arg] = [%s]\n"RESET, node->cmd, node->arg);
	printf(B_PURPLE"> execve() 함수용 커맨드 배열\n"RESET);
	printf(BLUE);
	print_double_str(node->args);
	printf(RESET);
	printf(B_PURPLE"> 리다이렉션 정보\n"RESET);
	printf("bin = %s\n", node->bin);
	printf("INPUT file name = %s\n", node->input_redir);
	printf("OUTPUT file name = %s\n", node->output_redir);
	printf("append = %d\n", node->append);
	printf("INPUT FD = %d\nOUTPUT FD = %d\n", node->input_fd, node->output_fd);
	printf("DIRECTORY = %s\n", node->dir);
	printf(B_WHITE"----------------------------------------------\n"RESET);
}

void	print_redir(t_control *con, t_lst *redir)
{
	int			i;
	t_redirect	*node;

	i = 0;
	node = redir->head;
	if (redir == con->redir)
		printf(B_PURPLE"> 전체 리다이렉션 리스트\n"RESET);
	if (redir == con->i_redir)
		printf(B_PURPLE"> 입력 리다이렉션 리스트\n"RESET);
	else if (redir == con->o_redir)
		printf(B_PURPLE"> 출력 리다이렉션 리스트\n"RESET);
	while (node)
	{
		printf(GREEN" o (노드 %d) "RESET, i);
		printf(BLUE);
		printf("[type] = %c [arg] = %s ", node->type, node->arg);
		printf("[fd] = %d\n", node->fd);
		printf(RESET);
		node = node->next;
		i++;
	}
}

void	print_control(t_control *con)
{
	if (!con->redir->head)
		printf(B_PURPLE"> 리다이렉션이 존재하지 않습니다.\n"RESET);
	else
		print_redir(con, con->redir);
	if (!con->i_redir->head)
		printf(B_PURPLE"> 입력 리다이렉션이 존재하지 않습니다.\n"RESET);
	else
		print_redir(con, con->i_redir);
	if (!con->o_redir->head)
		printf(B_PURPLE"> 출력 리다이렉션이 존재하지 않습니다.\n"RESET);
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
		printf(B_WHITE"----------------------------------------------\n"RESET);
		printf(B_BLUE"[파이프 NO. %d]\n"RESET, i);
		print_cmd(tmp->cmd);
		print_control(tmp->con);
		i++;
		tmp = tmp->next;
	}
}
