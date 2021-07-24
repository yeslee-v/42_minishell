/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:26:58 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/07/25 03:13:06 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf g_sh;

void	set_term_cursor(void)
{
	struct termios cursor;

	tcgetattr(0, &cursor);
	cursor.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(0, TCSANOW, &cursor);
}

int		print_tc(int tc)
{
	write(1, &tc, 1);
	return (1);
}

void	handle_eof(void)
{
	int x;
	int y;
	char *cm;
	char *ce;

	x = 0;
	y = 0;
	get_cursor_pos(&x, &y);
	tgetent(NULL, "xterm");
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	tputs(tgoto(cm, y + 11, x - 2), 1, print_tc);
	printf("exit\n");
	free_lexer(g_sh.lexer);
	free_token(g_sh.token);
	free_process(g_sh.process);
	exit(0);
}

void	check_input_syntax(char *cmd)
{
	int i;
	int pipe;

	if (!cmd)
		return ;
	i = -1;
	pipe = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '|')
			pipe = 1;
		else if (!ft_isspace(cmd[i]))
			pipe = 0;
	}
	if (pipe == 1)
		printf("this cmd end pipe\n");
}

void	set_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	check_input_syntax(g_sh.cmd);
	if (g_sh.cmd == NULL)
		handle_eof();
	if (ft_strcmp(g_sh.cmd, "exit") == 0)
		exit_shell(1);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_terminal(void)
{
	tcgetattr(0, &g_sh.term);
	g_sh.term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &g_sh.term);
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_process(void)
{
	t_token	*tmp;
	int	ret;
	char *new_cmd;

	ret = 0;
	tmp = NULL;
	g_sh.lexer = lexer(g_sh.cmd);
	if (g_sh.lexer->err == 1)
		exit_shell(0);
	ret = tokenizer(g_sh.lexer->lex);
	if (ret == 2)
	{
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
		g_sh.cmd = ft_strjoin_sp(g_sh.cmd, new_cmd);
		g_sh.lexer = lexer(g_sh.cmd);
		ret = tokenizer(g_sh.lexer->lex);
	}
	add_history(g_sh.cmd);
	rl_redisplay();
	if (ret == -1)
		return ;
	tmp = g_sh.token->head;
	while (tmp)
		tmp = parser(tmp);
	if (tmp != NULL)
		parser(tmp);
	print_system();
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
		tmp = ft_split_env(envp[i]);
		make_env(env, tmp[0], tmp[1]);
		ft_free_double((void **)tmp);
	}
	g_sh.env = env;
}
