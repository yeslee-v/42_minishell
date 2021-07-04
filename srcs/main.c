/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:30:39 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/04 19:16:32 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_conf	g_sh;

void	exit_shell(int num)
{
	printf("Good bye ~ !\n");
	exit(num);
}

void	print_token(t_lst *token)
{
	t_token	*temp;

	temp = token->head;
	while (temp)
	{
		printf("token = %s, type = %c, index = %d, st = %d, ed = %d\n",
				temp->token,
				temp->type,
				temp->i, temp->st, temp->ed);
		temp = temp->next;
	}
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

void	set_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	add_history(g_sh.cmd);
	rl_redisplay();
	lexer(g_sh.cmd);
	tokenizer(&g_sh, g_sh.lexer->lex);
	printf("cmd = %s\nlex = %s\n", g_sh.cmd, g_sh.lexer->lex);
	print_token(g_sh.token);
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
