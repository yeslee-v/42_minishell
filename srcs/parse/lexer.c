/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:17:44 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/21 17:18:16 by parkjaekw        ###   ########.fr       */
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

int		check_fd(char *cmd, int i)
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
	printf("i = %d\n", i);
	if (start == 1 && i == -1)
		return (1);
	else if (start == 1 && i >= 0 && (ft_isspace(cmd[i])) == 1)
		return (1);
	return (0);
}

void		mark_fd(char *lex, char type, int i)
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

static void	analyze_operator(char *lex, int ret, int *i)
{
	int fd_exist;

	fd_exist = 0;
	if (ret == 1)
		lex[*i] = 'P';
	else if (ret == 2)
	{
		fd_exist = check_fd(g_sh.cmd, *i - 1);
		if (fd_exist == 1)
			mark_fd(lex, 'H', *i - 1);
		lex[*i] = 'H';
		(*i)++;
		lex[*i] = 'H';
	}
	else if(ret == 3)
	{
		fd_exist = check_fd(g_sh.cmd, *i - 1);
		if (fd_exist == 1)
			mark_fd(lex, 'A', *i - 1);
		lex[*i] = 'A';
		(*i)++;
		lex[*i] = 'A';
	}
	else if (ret >= 4)
	{
		fd_exist = check_fd(g_sh.cmd, *i - 1);
		if (fd_exist == 1)
			mark_fd(lex, 'R', *i - 1);
		lex[*i] = 'R';
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
