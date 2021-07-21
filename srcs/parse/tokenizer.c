/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:28:05 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/20 11:41:42 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

static void		set_index(t_lst *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token->head;
	while (tmp)
	{
		if (tmp->type == 'S')
		{
			tmp->i = i;
			i++;
		}
		else if (ft_strchr("AIOHP", tmp->type))
		{
			if (tmp->type == 'P')
				i = -1;
			else
				i = 0;
			tmp->i = i;
			i++;
		}
		tmp = tmp->next;
	}
}

static void		set_type(t_lst *token)
{
	t_token	*tmp;

	tmp = token->head;
	while (tmp)
	{
		if (((ft_strcmp(tmp->token, PIPE)) == 0) && tmp != token->head)
			tmp->type = 'P';
		else if ((ft_strcmp(tmp->token, O_REDIR)) == 0)
			tmp->type = 'O';
		else if ((ft_strcmp(tmp->token, I_REDIR)) == 0)
			tmp->type = 'I';
		else if ((ft_strcmp(tmp->token, A_REDIR)) == 0)
			tmp->type = 'A';
		else if ((ft_strcmp(tmp->token, HEREDOC)) == 0)
			tmp->type = 'H';
		else
			tmp->type = 'S';
		tmp = tmp->next;
	}
}

static void		analyze_token(t_lst *token)
{
	set_type(token);
	set_index(token);
}

void			check_last_token(void)
{
	int status;
	pid_t	pid;
	char	*line;
	t_token	*node;
	t_lexer	*tmp;

	pid = fork();
	printf("pid %d\n", pid);
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	if (pid == 0)
	{
		node = g_sh.token->tail;
		if (!node)
			return ;
		else if (node->token)
		{
			if (node->token[0] == '|')
			{
				while (TRUE)
				{
					line = readline("> ");
					if (ft_strlen(line) > 0)
					{
						g_sh.cmd = ft_strjoin_sp(g_sh.cmd, line);
						tmp = lexer(g_sh.cmd);
						free_lexer(g_sh.lexer);
						g_sh.lexer = tmp;
						free_token(g_sh.token);
						g_sh.token = malloc(sizeof(t_lst));
						init_lst(g_sh.token);
						tokenizer(tmp->lex);
						free(line);
						break ;
					}
					rl_redisplay();
					free(line);
				}
			}
		}
		exit(0);
	}
}

void			tokenizer(char *lex)
{
	t_tool	tool;

	init_tool(&tool);
	while (lex[++(tool.i)])
	{
		if (tool.st == -1 && lex[tool.i] != 's')
		{
			if (lex[tool.i] == 'D' || lex[tool.i] == 'Q')
				tool.is_quote = 1;
			tool.st = tool.i;
		}
		if (tool.st >= 0 &&
			(lex[tool.i + 1] == 's' || lex[tool.i + 1] == '\0' ||
				(tool.is_quote == 0 && lex[tool.st] != lex[tool.i + 1])))
		{
			tool.ed = tool.i;
			make_token(g_sh.token, tool.st, tool.ed);
			tool.is_quote = 0;
			tool.st = -1;
			tool.ed = -1;
		}
	}
	analyze_token(g_sh.token);
	check_last_token();
}
