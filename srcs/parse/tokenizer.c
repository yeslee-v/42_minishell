/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:28:05 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/25 03:01:53 by parkjaekw        ###   ########.fr       */
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

static void		set_type(t_lst *token)
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
		else if (g_sh.lexer->lex[tmp->st] == 'F')
			tmp->type = 'F';
		else
			tmp->type = 'S';
		tmp = tmp->next;
	}
}

int				analyze_append_redir(t_token *node)
{
	int	fd;
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	fd = -2;
	if (!node)
		return (-1);
	else if ((ft_isnum(node->token[0])) == 1)
		fd = ft_atoi(node->token);
	if (fd == -1)
		printf("BraveShell: file descriptor out of range: Bad file "
				"descriptor\n");
	else if (fd > 255)
		printf("BraveShell: %d: Bad file descriptor\n", fd);
	while ((ft_isnum(node->token[i])) == 1)
		i++;
	while (node->token[i])
	{
		cnt++;
		i++;
	}
	printf("mark cnt = %d\n", cnt);
	return (cnt);
}

int				check_unexpected_token(t_token *node)
{
	if (node->next == NULL)
	{
		if (node->type == 'P')
			return (2);
		printf("BraveShell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	else if (node->next != NULL)
	{
		if (ft_strchr("AFHIOP", node->next->type))
		{
			if (node->type == 'P' && ft_strchr("FHIOA", node->next->type))
				return (1);
			else if (node->type == 'P')
			printf("BraveShell: syntax error near unexpected token `%s'\n",
					node->next->token);
			return (-1);
		}
	}
	return (1);
}

int				check_fd_token(t_token *node)
{
	int	fd;

	fd = ft_atoi(node->token);
	if (fd == -1)
	{
		printf("BraveShell: file descriptor out of range: Bad file "
				"descriptor\n");
		return (-1);
	}
	else if (fd > 255)
	{
		printf("BraveShell: %d: Bad file descriptor\n", fd);
		return (-1);
	}
	return (1);
}

int				analyze_syntax(t_lst *token)
{
	int		find_cmd;
	t_token	*tmp;
	t_token	*tail;
	int		ret;

	find_cmd = 0;
	tmp = token->head;
	tail = token->tail;
	ret = 0;
	while (tmp)
	{
		if (ft_strchr("AOIPH", tmp->type))
			ret = check_unexpected_token(tmp);
		if (ret == -1 || ret == 2)
			return (ret);
		tmp = tmp->next;
	}
	tmp = token->head;
	/*while (tmp)*/
	/*{*/
		/*if (tmp->type == 'F')*/
			/*ret = check_fd_token(tmp);*/
		/*if (ret == -1)*/
			/*return (-1);*/
		/*tmp = tmp->next;*/
	/*}*/
	/*tmp = token->head;*/
	while (tmp)
	{
		if (tmp->type == 'S')
		{
			if (tmp == token->head)
			{
				tmp->type = 'C';
				find_cmd = 1;
			}
			else if (find_cmd == 0 &&
						(tmp->prev != NULL && tmp->prev->type == 'T'))
			{
				tmp->type = 'C';
				find_cmd = 1;
			}
			else if (tmp->i == 0 && find_cmd == 0)
			{
				tmp->type = 'C';
				find_cmd = 1;
			}
			else if (tmp->prev != NULL && ft_strchr("IOA", tmp->prev->type))
				tmp->type = 'T';
			else if (tmp->prev != NULL && tmp->prev->type == 'H')
				tmp->type = 'D';
		}
		else if (tmp->type == 'P')
			find_cmd = 0;
		tmp = tmp->next;
	}
	return (ret);
}

static void		analyze_token(t_lst *token)
{
	set_type(token);
	set_index(token);
}

char	*unclosed_pipe(void)
{
	pid_t pid;
	int	fd[2];
	int status;
	char	*ret;
	char	*line;

	pipe(fd);
	ret = NULL;
	line = NULL;
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
		close(fd[1]);
		get_next_line(fd[0], &ret);
		if (ret != NULL)
			return (ret);
	}
	else if (pid == 0)
	{
		while (1)
		{
			line = readline("> ");
			if (line[0] != '\0')
			{
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				free(line);
				exit(0);
			}
			if (line)
				free(line);
			rl_redisplay();
		}
	}
	else
	{
		printf("fork error\n");
	}
	return (NULL);
}

/*
 *int			check_last_token(void)
 *{
 *    char	*line;
 *    t_token	*node;
 *    t_lexer	*tmp;
 *    int		ret;
 *
 *    node = g_sh.token->tail;
 *    if (!node)
 *        return (-1);
 *    else if (node->token)
 *    {
 *        if (node->token[0] == '|')
 *        {
 *            while (TRUE)
 *            {
 *                signal(SIGINT, SIG_DFL);
 *                signal(SIGQUIT, SIG_IGN);
 *                line = readline("> ");
 *                if (ft_strlen(line) > 0)
 *                {
 *                    g_sh.cmd = ft_strjoin_sp(g_sh.cmd, line);
 *                    tmp = lexer(g_sh.cmd);
 *                    free_lexer(g_sh.lexer);
 *                    printf("cmd = %s, tmp lex = %s\n",g_sh.cmd, tmp->lex);
 *                    g_sh.lexer = tmp;
 *                    free_token(g_sh.token);
 *                    g_sh.token = malloc(sizeof(t_lst));
 *                    init_lst(g_sh.token);
 *                    ret = tokenizer(tmp->lex);
 *                    free(line);
 *                    break ;
 *                }
 *                rl_redisplay();
 *                free(line);
 *            }
 *        }
 *    }
 *    return (analyze_syntax(g_sh.token));
 *}
 */

int				tokenizer(char *lex)
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
		if (tool.st >= 0 && ft_strchr("AH", lex[tool.st]))
		{
			tool.i += 1;
			tool.ed = tool.st + 1;
			make_token(g_sh.token, tool.st, tool.ed);
			tool.st = -1;
			tool.ed = -1;
		}
		else if (tool.st >= 0 && lex[tool.st] == 'P')
		{
			tool.ed = tool.i;
			make_token(g_sh.token, tool.st, tool.ed);
			tool.st = -1;
			tool.ed = -1;
		}
		else if (tool.st >= 0 &&
					(lex[tool.i + 1] == 's' || lex[tool.i + 1] == '\0' ||
					(tool.is_quote == 0 && lex[tool.st] != lex[tool.i + 1])))
		{
			tool.ed = tool.i;
			make_token(g_sh.token, tool.st, tool.ed);
			tool.st = -1;
			tool.ed = -1;
			tool.is_quote = 0;
		}
	}
	analyze_token(g_sh.token);
	return (analyze_syntax(g_sh.token));
}
