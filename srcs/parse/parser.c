/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 13:55:51 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/13 20:07:36 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_redir(t_token *tok, t_lst *syn, char *cmd, char *arg)
{
	make_syntax(syn, cmd, arg);
	cmd = ft_strdup(tok->token);
	arg = NULL;
}
t_lst	*init_syntax(void)
{
	t_lst *syn;

	syn = malloc(sizeof(t_lst));
	init_lst(syn);
	return (syn);
}

t_token	*parser(t_lst *process, t_token *tok)
{
	char	*cmd_t;
	char	*arg_t;
	t_lst	*syn;

	cmd_t = NULL;
	arg_t = NULL;
	syn = init_syntax();
	while (tok)
	{
		if (tok->i == 0 && tok->type == 'S')
			cmd_t = ft_strdup(tok->token);
		else if (tok->i >= 1 && tok->type == 'S')
			arg_t = ft_strjoin_sp(arg_t, tok->token);
		else if (tok->i == 0 && (ft_strchr("OIAH", tok->type)))
			parse_redir(tok, syn, cmd_t, arg_t);
		else if (tok->i == -1)
		{
			tok = tok->next;
			break ;
		}
		tok = tok->next;
	}
	if (cmd_t != NULL || arg_t != NULL)
		make_syntax(syn, cmd_t, arg_t);
	save_process(process, syn);
	return (tok);
}
