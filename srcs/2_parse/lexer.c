/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:17:44 by jaekpark          #+#    #+#             */
/*   Updated: 2021/08/03 00:05:47 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

t_lexer	*lexer(char *cmd)
{
	int		i;
	t_lexer	*lexer;

	if (!cmd)
		return (NULL);
	lexer = malloc(sizeof(t_lexer));
	init_lexer(lexer);
	lexer->lex = ft_strdup(cmd);
	ft_memset(lexer->lex, 0, ft_strlen(cmd));
	i = -1;
	while (cmd[++i])
		analyze_lexicon(lexer, cmd, &i);
	if (lexer->s_quote != 0)
		lexer->err = 1;
	return (lexer);
}
