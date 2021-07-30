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

	i = -1;
	if (!str || !target)
		return ;
	while (str[++i])
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

char	*ft_str_change(char *str, char *target, char *src)
{
	char *ret;
	int st;
	int ed;

	if (!str || !target || !src)
		return (NULL);
	ret = NULL;
	st = -1;
	ed = -1;
	get_target_pos(str, target, &st, &ed);
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

static void	convert_exit_status(t_token *tok)
{
	char *exit_status;

	if (!tok)
		return ;
	exit_status = ft_itoa(g_sh.exit_status);
	while (ft_strstr(tok->token, "$?"))
		tok->token = ft_str_change(tok->token, "$?", exit_status);
	free(exit_status);
}

char	*get_env_in_cmd(char *str)
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
			if (st == j || st == j - 1)
				return (NULL);
			else
				return (ft_strrdup(str, st, j - 1));
		}
	}
	return (NULL);
}

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
static void	convert_env(t_token *tok)
{
	int cnt;
	t_env *node;
	char *key;
	char *value;

	cnt = 0;
	node = g_sh.env->head;
	while (node)
	{
		key = ft_strjoin(ft_strdup("$"), node->key);
		value = node->value;
		while (ft_strstr(tok->token, key))
		{
			tok->token = ft_str_change(tok->token, key, value);
			cnt++;
		}
		free(key);
		node = node->next;
	}
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
		if (lex[i] == 'c')
			cnt++;
	}
	return (cnt);
}

char *strdup_only_char(char *lex, t_token *node)
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
		if (lex[i] == 'c')
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
			buf = strdup_only_char(tmp->lex, node);
			free(node->token);
			node->token = ft_strdup(buf);
			free(buf);
		}
		free_lexer(tmp);
		tmp = NULL;
		printf("token = %s\n", node->token);
		node = node->next;
	}
}

static void	set_meta_character(t_lst *token)
{
	t_token *tmp;
	/*char *exit_status;*/

	/*exit_status = ft_itoa(g_sh.exit_status);*/
	tmp = token->head;
	while (tmp)
	{
		if ((ft_strcmp(tmp->token, "~")) == 0)
		{
			free(tmp->token);
			tmp->token = ft_strdup(search_env_value("HOME", g_sh.env));
		}
		else if (ft_strstr(tmp->token, "$?"))
			convert_exit_status(tmp);
		else if (ft_strchr(tmp->token, '$'))
			convert_env(tmp);
		tmp = tmp->next;
	}
	/*free(exit_status);*/
}

void	set_env_null(t_lst *token)
{
	t_token *node;
	char *tmp;

	tmp = NULL;
	node = token->head;
	while (node)
	{
		while (1)
		{
			tmp = get_env_in_cmd(node->token);
			if (tmp != NULL)
			{
				node->token = ft_str_change(node->token, tmp, "");
				free(tmp);
			}
			if (tmp == NULL)
				break ;
		}
		node = node->next;
	}
}

void	analyze_token(t_lst *token)
{
	set_type(token);
	set_index(token);
	set_meta_character(token);
	set_env_null(token);
	remove_quote(token);
}
