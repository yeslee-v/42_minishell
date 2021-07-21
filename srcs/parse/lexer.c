/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:17:44 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/19 22:35:20 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

/*
 * echo hi |>a.txt
 * echo hi|<<>>
 * echo hi |>>a.txt
 * echo |>>
 */

static void	analyze_space(t_lexer *lexer, int i)
{
	if (!lexer)
		return ;
	if (lexer->s_quote > TRUE)
		lexer->lex[i] = 'c';
	else if (lexer->s_quote == FALSE)
		lexer->lex[i] = 's';
}

static void	analyze_quote(t_lexer *lexer, char c, int i)
{
	(void)c;
	printf("enter analyze_quote\n");
	if (lexer->s_quote == lexer->e_quote)
	{
		lexer->lex[i] = lexer->e_quote;
		lexer->s_quote = 0;
		lexer->e_quote = 0;
	}
	else
		lexer->lex[i] = 'c';
}

	/*
	 *2 == hdoc , 3 == append redir
	 */
static void	analyze_operator(char *lex, int ret, int *i)
{
	char	c;

	c = 0;
	if (ret == 2 || ret == 3)
	{
		if (ret == 2)
			c = 'H';
		else
			c = 'A';
		lex[*i] = c;
		(*i)++;
		lex[*i] = c;
	}
	else if (ret == 1)
		lex[*i] = 'P';
	else if (ret >= 4)
		lex[*i] = 'R';
}

void	analyze_command(t_lexer *lexer, char *cmd, int *i)
{
	int	ret;

	if (ft_isalnum(cmd[*i]))
		lexer->lex[*i] = 'c';
	else if (lexer->s_quote == 0 && ft_isquote(cmd[*i]))
	{
		lexer->s_quote = ft_isquote(cmd[*i]);
		if (lexer->s_quote >= 1)
			lexer->lex[*i] = lexer->s_quote;
	}
	else if (lexer->s_quote && ft_isquote(cmd[*i]))
	{
		lexer->e_quote = ft_isquote(cmd[*i]);
		if (lexer->e_quote >= 1)
			analyze_quote(lexer, cmd[*i], *i);
	}
	else if (ft_isspace(cmd[*i]))
		analyze_space(lexer, *i);
	else if (lexer->s_quote == 0 && ft_isspec(cmd, *i))
	{
		ret = ft_isspec(cmd, *i);
		analyze_operator(lexer->lex, ret, i);
	}	
	else
		lexer->lex[*i] = 'c';
}

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
		analyze_command(lexer, cmd, &i);
	if (lexer->s_quote != 0)
		lexer->err = 1;
	return (lexer);
}
