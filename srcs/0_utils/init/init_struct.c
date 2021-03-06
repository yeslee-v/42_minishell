/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 18:15:00 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 03:00:24 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	init_lst(g_sh.process);
	init_lst(g_sh.token);
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
