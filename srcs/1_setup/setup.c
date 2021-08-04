/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:26:58 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/08/04 16:55:03 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

int	set_cmd_after_pipe(void)
{
	char	*new_cmd;
	int		ret;

	ret = 0;
	new_cmd = NULL;
	free_lexer(g_sh.lexer);
	g_sh.lexer = NULL;
	free_token(g_sh.token);
	g_sh.token = NULL;
	if (g_sh.token == NULL)
	{
		g_sh.token = malloc(sizeof(t_lst));
		init_lst(g_sh.token);
	}
	new_cmd = unclosed_pipe();
	if (new_cmd == NULL)
		return (-1);
	g_sh.cmd = ft_strcjoin(g_sh.cmd, new_cmd, ' ');
	free(new_cmd);
	g_sh.lexer = lexer(g_sh.cmd);
	ret = tokenizer(g_sh.lexer->lex);
	return (ret);
}

void	set_prompt(void)
{
	int x;
	int y;
	int a;
	char buf[521];

	g_sh.cmd = readline(PROMPT);
	if (g_sh.cmd == NULL)
	{
		move_cursor("exit\n", g_sh.col - 1 , 2);
		free_conf(&g_sh);
		free_env(g_sh.env);
		exit(0);
	}
}

int	set_process(void)
{
	t_token	*tmp;
	int		ret;

	ret = 0;
	tmp = NULL;
	if (!g_sh.cmd)
		return (1);
	g_sh.lexer = lexer(g_sh.cmd);
	if (g_sh.lexer->err == 1)
	{
		error_with_message(ERR_QUOTE, 258);
		return (1);
	}
	ret = tokenizer(g_sh.lexer->lex);
	while (ret == 2)
		ret = set_cmd_after_pipe();
	add_history(g_sh.cmd);
	rl_redisplay();
	if (ret == -1)
		return (1);
	tmp = g_sh.token->head;
	while (tmp)
		tmp = parser(tmp);
	if (tmp != NULL)
		parser(tmp);
	return (0);
}

void	set_env(char **envp)
{
	int		i;
	char	**tmp;
	t_lst	*env;

	i = -1;
	tmp = NULL;
	env = malloc(sizeof(t_lst));
	init_lst(env);
	g_sh.envp = envp;
	while (envp[++i])
	{
		tmp = split_env(envp[i]);
		make_env(env, tmp[0], tmp[1]);
		ft_free_double((void **)tmp);
	}
	g_sh.env = env;
}
