/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:30:39 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/13 20:40:47 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_conf	g_sh;

void	exit_shell(int num)
{
	printf("exit\n");
	exit(num);
}

void	parse(void)
{
	t_token	*tmp;

	tmp = NULL;
	lexer(g_sh.cmd);
	tokenizer(&g_sh, g_sh.lexer->lex);
	g_sh.process = malloc(sizeof(t_lst));
	init_lst(g_sh.process);
	tmp = g_sh.token->head;
	while (tmp)
		tmp = parser(g_sh.process, tmp);
	if (tmp != NULL)
		parser(g_sh.process, tmp);
	print_system();
}

void	set_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	if (ft_strcmp(g_sh.cmd, "exit") == 0)
		exit_shell(0);
	add_history(g_sh.cmd);
	rl_redisplay();
	parse();
		if (g_sh.lexer->err == 1)
		printf("quote err\n");
	free(g_sh.cmd);
	free_lexer(g_sh.lexer);
}

int		main(int ac, char **av, char **envp)
{
	int	ret;

	if (!ac || !av)
		return (-1);
	ret = ac;
	set_env(envp);
	set_terminal();
	while (ret)
	{
		set_signal();
		set_prompt();
	}
}
