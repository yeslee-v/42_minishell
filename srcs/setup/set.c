/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:26:58 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/07/27 18:02:08 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf	g_sh;

static int	set_cmd_after_pipe(void)
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
	printf("hell0\n");
	g_sh.cmd = ft_strjoin_sp(g_sh.cmd, new_cmd);
	free(new_cmd);
	g_sh.lexer = lexer(g_sh.cmd);
	ret = tokenizer(g_sh.lexer->lex);
	return (ret);
}

void	set_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	if (g_sh.cmd == NULL)
	{
		move_cursor("exit", 11, 2);
		exit(0);
	}
	if (ft_strcmp(g_sh.cmd, "exit") == 0)
		exit_shell(1);
}

void	set_process(void)
{
	t_token	*tmp;
	int		ret;

	ret = 0;
	tmp = NULL;
	g_sh.lexer = lexer(g_sh.cmd);
	if (g_sh.lexer->err == 1)
		exit_shell(0);
	ret = tokenizer(g_sh.lexer->lex);
	while (ret == 2)
		ret = set_cmd_after_pipe();
	add_history(g_sh.cmd);
	rl_redisplay();
	if (ret == -1)
		return ;
	tmp = g_sh.token->head;
	while (tmp)
		tmp = parser(tmp);
	if (tmp != NULL)
		parser(tmp);
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
