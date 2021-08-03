#include "../../includes/minishell.h"

void	analyze_space(t_lexer *lexer, int i)
{
	if (!lexer)
		return ;
	if (lexer->s_quote > TRUE)
	{
		if (lexer->s_quote == 68)
			lexer->lex[i] = 'd';
		else if (lexer->s_quote == 81)
			lexer->lex[i] = 'q';
	}
	else if (lexer->s_quote == FALSE)
		lexer->lex[i] = 's';
}

void	analyze_quote_pair(t_lexer *lexer, char c, int i)
{
	(void)c;
	if (lexer->s_quote == lexer->e_quote)
	{
		lexer->lex[i] = lexer->e_quote;
		lexer->s_quote = 0;
		lexer->e_quote = 0;
	}
	else if (lexer->s_quote == 68)
		lexer->lex[i] = 'd';
	else if (lexer->s_quote == 81)
		lexer->lex[i] = 'q';
}

void	analyze_operator(char *lex, int ret, int *i)
{
	if (ret == 1)
		lex[*i] = 'P';
	else if (ret == S_HDOC)
	{
		lex[*i] = 'H';
		(*i)++;
		lex[*i] = 'H';
	}
	else if (ret == S_AREDIR)
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

void	check_in_quote(t_lexer *lexer, int i)
{
	if (lexer->s_quote == 68)
		lexer->lex[i] = 'd';
	else if (lexer->s_quote == 81)
		lexer->lex[i] = 'q';
	else
		lexer->lex[i] = 'c';
}

void	analyze_lexicon(t_lexer *lexer, char *cmd, int *i)
{
	int	ret;

	if (ft_isalnum(cmd[*i]))
		check_in_quote(lexer, *i);
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
			analyze_quote_pair(lexer, cmd[*i], *i);
	}
	else if (ft_isspace(cmd[*i]))
		analyze_space(lexer, *i);
	else if (lexer->s_quote == 0 && ft_isspec(cmd, *i))
	{
		ret = ft_isspec(cmd, *i);
		analyze_operator(lexer->lex, ret, i);
	}	
	else
		check_in_quote(lexer, *i);
}
