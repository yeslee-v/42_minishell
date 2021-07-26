/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:17:44 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/26 20:43:56 by parkjaekw        ###   ########.fr       */
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

int		check_precede_fd(char *cmd, int i)
{
	int start;

	start = 0;
	if (!cmd)
		return (0);
	while (i >= 0)
	{
		if ((ft_isnum(cmd[i])) == 1)
		{
			if (start == 0)
				start = 1;
			i--;
		}
		else
			break;
	}
	if (start == 1 && i == -1)
		return (1);
	else if (start == 1 && i >= 0 && (ft_strchr(" <>", cmd[i])))
		return (1);
	return (0);
}

int		check_follow_fd(char *cmd, int i)
{
	int size;
	int start;

	size = 0;
	start = 0;
	if (!cmd || cmd[i] != '&')
		return (0);
	size = ft_strlen(cmd);
	if (i >= size)
		return (0);
	printf("ok\n");
	if (cmd[i] == '&')
		i++;
	while (i < size)
	{
		if ((ft_isnum(cmd[i])) == 1)
			start = 1;
		else
			break;
		i++;
	}
	if (start == 1 && cmd[i] == '\0')
		return (1);
	else if (start == 1 && i < size && ft_strchr(" <>", cmd[i]))
		return (1);
	return (0);
}

void		mark_precede_fd(char *lex, char type, int i)
{
	if (!lex)
		return ;
	while (i >= 0)
	{
		if ((ft_isnum(g_sh.cmd[i])) == 1)
		{
			lex[i] = type;
			i--;
		}
		else
			break;
	}
}

void		mark_follow_fd(char *lex, char type, int *i)
{
	int size;

	size = ft_strlen(g_sh.cmd);
	(*i)++;
	if (*i >= size)
		return ;
	if (g_sh.cmd[*i] == '&')
		lex[*i] = 'f';
	printf("mark follow fd\n");
	if (!lex)
		return ;
	if (g_sh.cmd[*i] == '&')
		lex[(*i)++] = '&';
	while (*i < size)
	{
		if ((ft_isnum(g_sh.cmd[*i])) == 1)
			lex[*i] = type;
		else
			break ;
		(*i)++;
	}
}

static void	analyze_operator(char *lex, int ret, int *i)
{
	if (ret == 1)
		lex[*i] = 'P';
	else if (ret == S_HDOC)
	{
		lex[*i] = 'H';
		(*i)++;
		lex[*i] = 'H';
	}
	else if(ret == S_AREDIR)
	{
		lex[*i] = 'A';
		(*i)++;
		lex[*i] = 'A';
	}
	else if (ret >= S_IREDIR)
	{
		if (ret == S_IREDIR)
			lex[*i] = 'I';
		else if (ret == S_OREDIR)
			lex[*i] = 'O';
		}
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
