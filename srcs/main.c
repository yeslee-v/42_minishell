/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:30:39 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/02 20:46:06 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_conf	g_sh;

void	exit_shell(int num)
{
	printf("Good bye ~ !\n");
	exit(num);
}

int		print_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	add_history(g_sh.cmd);
	return (1);
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

void	marker(char *cmd)
{
	int i;
	char *ret;
	int s_quote;
	int e_quote;
	int is_quote;

	i = -1;
	is_quote = 0;
	ret = ft_strdup(cmd);
	ft_memset(ret, 0, ft_strlen(ret));
	while (cmd[++i])
	{
		if (ft_isalnum(cmd[i]))
			ret[i] = 'c';
		if (is_quote == 0 && ((s_quote = ft_isquote(cmd[i])) >= 1))
		{
			ret[i] = s_quote;
			is_quote = s_quote;
		}
		else if (is_quote == s_quote && ((e_quote = ft_isquote(cmd[i])) >= 1))
		{
			if (s_quote == e_quote)
			{
				ret[i] = e_quote;
				is_quote = 0;
			}
			else
				ret[i] = cmd[i];
		}
		else if (ft_isspace(cmd[i]))
		{
			if (is_quote > TRUE)
				ret[i] = '2';
			else if (is_quote == FALSE)
				ret[i] = '1';
		}
	}
	if (is_quote != 0)
		printf("quote err\n");
	g_sh.lex = ret;
}

/*
 *void	tokenizer(char *cmd)
 *{
 *    int i;
 *    t_flag flag;
 *
 *    i = 0;
 *    init_flag(&flag);
 *    while (ft_isspace(cmd[i]))
 *        i++;
 *    while (cmd[i])
 *    {
 *        if ()
 *    }
 *
 *}
 */

void	lexer(void)
{
	
}

int		main(int ac, char **av, char **envp)
{
	int	ret;

	(void)av;
	ret = ac;
	g_sh.env = envp;
	tcgetattr(0, &g_sh.term);
	g_sh.term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &g_sh.term);
	while (ret)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		print_prompt();
		if ((ft_strcmp(g_sh.cmd, "exit")) == 0)
		{
			exit_shell(0);
		}
		add_history(g_sh.cmd);
		rl_redisplay();
		marker(g_sh.cmd);
		printf("cmd = %s\nlex = %s\n", g_sh.cmd, g_sh.lex);
		free(g_sh.cmd);
		free(g_sh.lex);
	}
}
