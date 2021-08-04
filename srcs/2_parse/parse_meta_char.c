#include "../../includes/minishell.h"

extern t_conf	g_sh;

static int	convert_exit_status(t_token *tok, t_lexer *tmp, int i)
{
	int		st;
	char	*exit_status;

	exit_status = ft_itoa(g_sh.exit_status);
	st = i;
	tok->token = ft_str_change(tok->token, exit_status, st, st + 1);
	free_lexer(tmp);
	free(exit_status);
	return (1);
}

static int	convert_env(t_token *tok, t_lexer *tmp, int i)
{
	char	*env;
	char	*value;
	int		size;
	int		st;

	st = i;
	env = get_env_in_cmd(&(tok->token[i]), &(tmp->lex[i]));
	size = ft_strlen(env) - 1;
	if (env != NULL)
	{
		value = search_env_value(env + 1, g_sh.env);
		if (value != NULL)
			tok->token = ft_str_change(tok->token, value, st, st + size);
		else if (value == NULL)
			tok->token = ft_str_change(tok->token, "", st, st + size);
	}
	else if (env == NULL)
	{
		free_lexer(tmp);
		return (0);
	}
	if (env)
		free(env);
	free_lexer(tmp);
	return (1);
}

static int	convert_argv(t_token *tok, t_lexer *tmp, int i)
{
	int	st;

	st = i;
	tok->token = ft_str_change(tok->token, "", st, st + 1);
	free_lexer(tmp);
	return (1);
}

static int	convert_meta_char(t_token *tok)
{
	t_lexer	*tmp;
	char	*str;
	int		i;

	i = -1;
	str = tok->token;
	if (!tok)
		return (-1);
	tmp = lexer(str);
	while (str[++i])
	{
		if (str[i] == '$' && tmp->lex[i] != 'q')
		{
			if (str[i + 1] != '\0' && str[i + 1] == '?')
				return (convert_exit_status(tok, tmp, i));
			else if (str[i + 1] != '\0' && ((ft_isnum(str[i + 1])) == 1))
				return (convert_argv(tok, tmp, i));
			else
				return (convert_env(tok, tmp, i));
		}
	}
	free_lexer(tmp);
	return (0);
}

void	set_meta_character(t_lst *token)
{
	int		ret;
	t_token	*tmp;

	tmp = token->head;
	while (tmp)
	{
		ret = 1;
		if ((ft_strcmp(tmp->token, "~")) == 0)
		{
			free(tmp->token);
			tmp->token = ft_strdup(search_env_value("HOME", g_sh.env));
		}
		while (ret == 1)
			ret = convert_meta_char(tmp);
		tmp = tmp->next;
	}
}
