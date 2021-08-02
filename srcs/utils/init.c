/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:15:00 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/02 14:04:23 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	init_cmd(t_cmd *node)
{
	node->arg = NULL;
	node->args = NULL;
	node->cmd = NULL;
	node->append = 0;
	node->input_fd = -1;
	node->output_fd = -1;
	node->bin = NULL;
	node->input_redir = NULL;
	node->output_redir = NULL;
}

void	init_config(void)
{
	g_sh.lexer = NULL;
	g_sh.process = malloc(sizeof(t_lst));
	g_sh.token = malloc(sizeof(t_lst));
	g_sh.x = 0;
	g_sh.y = 0;
	init_lst(g_sh.process);
	init_lst(g_sh.token);
}

void	init_tool(t_tool *tool)
{
	tool->i = -1;
	tool->is_quote = 0;
	tool->st = -1;
	tool->ed = -1;
	tool->a_redir = 0;
	tool->redir = 0;
	tool->pipe = 0;
	tool->heredoc = 0;
}

void	init_lexer(t_lexer *lexer)
{
	lexer->is_quote = 0;
	lexer->s_quote = 0;
	lexer->e_quote = 0;
	lexer->err = 0;
	lexer->lex = NULL;
}

void	init_lst(t_lst *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

void	init_control(t_control *con)
{
	con->redir = malloc(sizeof(t_lst));
	con->o_redir = malloc(sizeof(t_lst));
	con->i_redir = malloc(sizeof(t_lst));
	init_lst(con->redir);
	init_lst(con->o_redir);
	init_lst(con->i_redir);
}
