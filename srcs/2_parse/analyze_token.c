#include "../../includes/minishell.h"

extern t_conf	g_sh;

static void	set_index(t_lst *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token->head;
	while (tmp)
	{
		if (tmp->type == 'P')
		{
			i = -1;
			tmp->i = i;
		}
		else
			tmp->i = i;
		tmp = tmp->next;
		i++;
	}
}

static void	set_type(t_lst *token)
{
	t_token	*tmp;

	tmp = token->head;
	while (tmp)
	{
		if (((ft_strcmp(tmp->token, PIPE)) == 0) && tmp != token->head)
			tmp->type = 'P';
		else if (ft_strchr("IO", g_sh.lexer->lex[tmp->st]))
		{
			if (g_sh.cmd[tmp->ed] == '<')
				tmp->type = 'I';
			else if (g_sh.cmd[tmp->ed] == '>')
				tmp->type = 'O';
		}
		else if (g_sh.lexer->lex[tmp->st] == 'A')
			tmp->type = 'A';
		else if (g_sh.lexer->lex[tmp->st] == 'H')
			tmp->type = 'H';
		else
			tmp->type = 'S';
		tmp = tmp->next;
	}
}

void	analyze_token(t_lst *token)
{
	set_type(token);
	set_index(token);
	set_meta_character(token);
}
