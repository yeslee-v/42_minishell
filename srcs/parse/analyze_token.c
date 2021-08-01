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

void	get_target_pos(char *str, char *target, int *st, int *ed)
{
	int i;

	i = *st;
	if (!str || !target)
		return ;
	while (str[i])
	{
		if (str[i] == target[0])
		{
			if (ft_strncmp(&str[i], target, ft_strlen(target)) == 0)
			{
				*st = i;
				*ed = i + (ft_strlen(target) - 1);
				return ;
			}
		}
		i++;
	}
}



char	*ft_strstr(char *str, char *src)
{
	int i;

	i = -1;
	if (!str || !src)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == src[0])
		{
			if ((ft_strncmp(&str[i], src, ft_strlen(src))) == 0)
				return (&str[i]);
		}
	}
	return (NULL);
}

char	*ft_str_change(char *str, char *src, int st, int ed)
{
	char *ret;

	if (!str || !src || st < 0 || ed < 0)
		return (NULL);
	ret = NULL;
	if (st == -1 && ed == -1)
		return (NULL);
	if (st == 0)
	{
		ret = ft_strdup(src);
		ret = ft_strjoin(ret, &str[ed + 1]);
	}
	else
	{
		ret = ft_strrdup(str, 0, st - 1);
		ret = ft_strjoin(ret, src);
		ret = ft_strjoin(ret, &str[ed + 1]);
	}
	free(str);
	return (ret);
}

/*static void	convert_exit_status(t_token *tok)*/
/*{*/
	/*int i;*/
	/*t_lexer *tmp;*/
	/*char *exit_status;*/

	/*tmp = lexer(tok->token);*/
	/*i = -1;*/
	/*if (!tok)*/
		/*return ;*/
	/*exit_status = ft_itoa(g_sh.exit_status);*/
	/*while (tok->token[++i])*/
	/*{*/
		/*if (tok->token[i] == '$' && tmp->lex[i] != 'q')*/
		/*{*/
				
		/*}*/
	/*}*/
	/*tok->token = ft_str_change(tok->token, "$?", exit_status);*/
	/*free(exit_status);*/
/*}*/



int	check_env_in_cmd(char *str)
{
	char *ret;
	int st;
	int i;
	int j;

	ret = NULL;
	st = -1;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			j = i;
			st = i;
			while (str[++j])
			{
				if ((ft_isalpha(str[j])) == 0)
					break ;
			}
			if ((st == j || st == j - 1) && str[j] != '\0')
				return (0);
			else
				return (1);
		}
	}
	return (0);
}
/*static void	convert_env(t_token *tok)*/
/*{*/
	/*t_env *node;*/
	/*[>char *pos;<]*/
	/*[>char *value;<]*/

	/*node = g_sh.env->head;*/
	/*set_env_null(g_sh.token);*/
	/*while (tok)*/
	/*{*/
		/*printf("token = %s\n", tok->token);*/
		/*tok = tok->next;*/
	/*}*/
/*}*/

int get_arg_cnt(char *lex)
{
	int i;
	int cnt;

	i = -1;
	cnt = 0;
	if (!lex)
		return (-1);
	while (lex[++i])
	{
		if (ft_strchr("dqsc", lex[i]))
			cnt++;
	}
	return (cnt);
}

int get_char_cnt(char *lex)
{
	int i;
	int cnt;

	i = -1;
	cnt = 0;
	if (!lex)
		return (-1);
	while (lex[++i])
	{
		if (ft_strchr("dqc", lex[i]))
			cnt++;
	}
	return (cnt);
}

char *token_dup_only_char(char *lex, t_token *node)
{
	char *ret;
	int i;
	int j;
	int size;

	i = -1;
	j = 0;
	if (!lex || !node)
		return (NULL);
	size = get_char_cnt(lex);
	ret = malloc(sizeof(char) * (size + 1));
	while (lex[++i])
	{
		if (ft_strchr("dqc", lex[i]))
		{
			ret[j] = node->token[i];
			j++;
		}
	}
	ret[size] = '\0';
	return (ret);
}

int	check_quote_exist(char *lex)
{
	int i;

	i = 0;
	if (!lex)
		return (-1);
	while (lex[i])
	{
		if (ft_strchr("DQ", lex[i]))
			return (1);
		i++;
	}
	return (0);
}

void remove_quote(t_lst *token)
{
	t_token *node;
	t_lexer *tmp;
	char *buf;
	int i;

	i = -1;
	buf = NULL;
	if (!token)
		return ;
	node = token->head;
	while (node)
	{
		tmp = lexer(node->token);
		if ((check_quote_exist(tmp->lex)) == 1)
		{
			buf = token_dup_only_char(tmp->lex, node);
			free(node->token);
			node->token = ft_strdup(buf);
			free(buf);
		}
		free_lexer(tmp);
		tmp = NULL;
		node = node->next;
	}
}

char *strdup_only_char(char *lex, char *str)
{
	char *ret;
	int i;
	int j;
	int size;

	i = -1;
	j = 0;
	if (!lex || !str)
		return (NULL);
	size = get_arg_cnt(lex);
	ret = malloc(sizeof(char) * (size + 1));
	while (lex[++i])
	{
		if (ft_strchr("dqsc", lex[i]))
		{
			ret[j] = str[i];
			j++;
		}
	}
	ret[size] = '\0';
	return (ret);
}

void remove_arg_quote(char **arg)
{
	char *buf;
	t_lexer *tmp;

	tmp = lexer(*arg);
	buf = NULL;
	if ((check_quote_exist(tmp->lex)) == 1)
	{
		buf = strdup_only_char(tmp->lex, *arg);
		free(*arg);
		*arg = ft_strdup(buf);
		free(buf);
	}
	free_lexer(tmp);
	tmp = NULL;
}

int ft_envchar(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*get_env_in_cmd(char *str, char *lex)
{
	char *ret;
	int st;
	int i;
	int j;

	ret = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && lex[i] != 'q')
		{
			j = i;
			st = i;
			while (str[++j])
			{
				if ((ft_envchar(str[j])) == 0)
					break ;
			}
			if (st == j || st == j - 1)
				return (NULL);
			else
				return (ft_strrdup(str, st, j - 1));
		}
	}
	return (NULL);
}

static int convert_exit_status(t_token *tok, t_lexer *tmp, int i)
{
	int st;
	char *exit_status;

	exit_status = ft_itoa(g_sh.exit_status);
	st = i;
	tok->token = ft_str_change(tok->token, exit_status, st, st + 1);
	free_lexer(tmp);
	free(exit_status);
	return (1);
}

static int	convert_env(t_token *tok, t_lexer *tmp, int i)
{
	char *env;
	char *value;
	int st;

	st = i;
	env = get_env_in_cmd(&(tok->token[i]), &(tmp->lex[i]));
	if (env != NULL)
	{
		value = search_env_value(env + 1, g_sh.env);
		if (value != NULL)
			tok->token = ft_str_change(tok->token, value, st, st + ft_strlen(env) - 1);
		else if (value == NULL)
			tok->token = ft_str_change(tok->token, "", st, st + ft_strlen(env) - 1);
	}
	else if (env == NULL)
		return (0);
	if (env)
		free(env);
	free_lexer(tmp);
	return (1);
}

static int convert_argv(t_token *tok, t_lexer *tmp, int i)
{
	int st;

	st = i;
	tok->token = ft_str_change(tok->token, "", st, st + 1);
	free_lexer(tmp);
	return (1);
}

static int convert_meta_char(t_token *tok)
{
	t_lexer *tmp;
	int i;

	i = -1;	
	if (!tok)
		return (-1);
	tmp = lexer(tok->token);
	while (tok->token[++i])
	{
		if (tok->token[i] == '$' && tmp->lex[i] != 'q')
		{
			if (tok->token[i + 1] != '\0' && tok->token[i + 1] == '?')
				return (convert_exit_status(tok, tmp, i));
			else if (tok->token[i + 1] != '\0' && ((ft_isnum(tok->token[i + 1])) == 1))
				return (convert_argv(tok, tmp, i));
			else
				return (convert_env(tok, tmp, i));
		}
	}
	free_lexer(tmp);
	return (0);
}

static void	set_meta_character(t_lst *token)
{
	int ret;
	t_token *tmp;

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

void	analyze_token(t_lst *token)
{
	set_type(token);
	set_index(token);
	set_meta_character(token);
}
