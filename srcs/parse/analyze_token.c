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

static void	convert_env(t_token *tok)
{
	t_env *node;
	char *key;
	char *value;

	node = g_sh.env->head;
	while (node)
	{
		key = ft_strjoin(ft_strdup("$"), node->key);
		value = node->value;
		while (ft_strstr(tok->token, key))
			tok->token = ft_str_change(tok->token, key, value);
		free(key);
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

void	analyze_token(t_lst *token)
{
	set_type(token);
	set_index(token);
	set_meta_character(token);
}
