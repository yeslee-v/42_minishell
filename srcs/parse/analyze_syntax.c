#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	mark_type(t_token *tmp, char type, int *find_cmd)
{
	tmp->type = type;
	if (type == 'C')
		*find_cmd = 1;
}

int	check_unexpected_token(t_token *node)
{
	if (node->next == NULL)
	{
		if (node->type == 'P')
			return (2);
		printf("BraveShell: syntax error near unexpected token `newline'\n");
		g_sh.exit_status = ERRNO_UNEXPECTED_TOKEN;
		return (-1);
	}
	else if (node->next != NULL)
	{
		if (ft_strchr("AFHIOP", node->next->type))
		{
			if (node->type == 'P' && ft_strchr("FHIOA", node->next->type))
				return (1);
			printf(ERR_TOKEN" `%s'\n", node->next->token);
			g_sh.exit_status = ERRNO_UNEXPECTED_TOKEN;
			return (-1);
		}
	}
	return (1);
}

int	check_type(t_lst *token, t_token *tmp, int find_cmd)
{
	if (tmp == token->head)
		return (1);
	else if (find_cmd == 0 && (tmp->prev != NULL && tmp->prev->type == 'T'))
		return (1);
	else if (tmp->i == 0 && find_cmd == 0)
		return (1);
	else if (tmp->prev != NULL && ft_strchr("IOA", tmp->prev->type))
		return (2);
	else if (tmp->prev != NULL && tmp->prev->type == 'H')
		return (3);
	return (0);
}

int	analyze_unexpected_token(t_token *tok)
{
	t_token	*tmp;
	int		ret;

	ret = 0;
	tmp = tok;
	while (tmp)
	{
		if (ft_strchr("AOIPH", tmp->type))
			ret = check_unexpected_token(tmp);
		if (ret == -1 || ret == 2)
			return (ret);
		tmp = tmp->next;
	}
	return (ret);
}

int	analyze_syntax(t_lst *token)
{
	t_token	*tmp;
	int		find_cmd;
	int		ret;

	find_cmd = 0;
	tmp = token->head;
	ret = analyze_unexpected_token(tmp);
	if (ret == -1 || ret == 2)
		return (ret);
	while (tmp)
	{
		if (tmp->type == 'S')
		{
			if ((check_type(token, tmp, find_cmd)) == 1)
				mark_type(tmp, 'C', &find_cmd);
			else if ((check_type(token, tmp, find_cmd)) == 2)
				mark_type(tmp, 'T', &find_cmd);
			else if ((check_type(token, tmp, find_cmd)) == 3)
				mark_type(tmp, 'D', &find_cmd);
		}
		else if (tmp->type == 'P')
			find_cmd = 0;
		tmp = tmp->next;
	}
	return (ret);
}
