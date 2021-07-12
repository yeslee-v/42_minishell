/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 15:35:59 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/12 15:55:11 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern t_conf g_sh;

void	free_lexer(t_lexer *lexer)
{
	if (lexer->lex != NULL)
		free(lexer->lex);
	if (lexer != NULL)
		free(lexer);
}
