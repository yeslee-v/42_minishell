/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:30:39 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/03 16:36:10 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_conf	g_sh;

void	exit_shell(int num)
{
	printf("Good bye ~ !\n");
	exit(num);
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

void	analyze_space(t_lexer *lexer, int i)
{
	if (!lexer)
		return ;
	if (lexer->s_quote > TRUE)
		lexer->lex[i] = 'T';
	else if (lexer->s_quote == FALSE)
		lexer->lex[i] = 'F';
}

void	analyze_quote_pair(t_lexer *lexer, char c, int i)
{
	if (lexer->s_quote == lexer->e_quote)
	{
		lexer->lex[i] = lexer->e_quote;
		lexer->s_quote = 0;
		lexer->e_quote = 0;
	}
	else
		lexer->lex[i] = c;
}

void	lexer(char *cmd)
{
	int		i;
	t_lexer	*lexer;

	i = -1;
	lexer = malloc(sizeof(t_lexer));
	init_lexer(lexer);
	while (cmd[++i])
	{
		if (ft_isalnum(cmd[i]))
			lexer->lex[i] = 'c';
		if (lexer->s_quote == 0 && ((lexer->s_quote = ft_isquote(cmd[i])) >= 1))
			lexer->lex[i] = lexer->s_quote;
		else if (lexer->s_quote && ((lexer->e_quote = ft_isquote(cmd[i])) >= 1))
			analyze_quote_pair(lexer, cmd[i], i);
		else if (ft_isspace(cmd[i]))
			analyze_space(lexer, i);
	}
	if (lexer->s_quote != 0)
		lexer->err = 1;
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

void	set_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	add_history(g_sh.cmd);
	rl_redisplay();
	lexer(g_sh.cmd);
	printf("cmd = %s\nlex = %s\n", g_sh.cmd, g_sh.lexer->lex);
	if ((ft_strcmp(g_sh.cmd, "exit")) == 0)
		exit_shell(0);
	if (g_sh.lexer->err == 1)
		printf("quote err\n");
	free(g_sh.cmd);
	free_lexer(g_sh.lexer);
}

int		main(int ac, char **av, char **envp)
{
	int	ret;

	(void)av;
	ret = ac;
	g_sh.env = envp;
	set_terminal();
	while (ret)
	{
		set_signal();
		set_prompt();
	}
}
