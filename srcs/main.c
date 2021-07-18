/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:30:39 by jaekpark          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/07/18 16:22:16 by yeslee           ###   ########.fr       */
=======
/*   Updated: 2021/07/18 17:37:49 by parkjaekw        ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_conf	g_sh;

void	get_cursor_pos(int *x, int *y)
{
	int ret;
	int	flag;
	char ch;

	flag = 0;
	init_pos(x, y);
	set_term_cursor();
	write(0, "\033[6n", 4);
	while (1)
	{
		ret = read(0, &ch, 1);
		if (!ret)
		{
			tcsetattr(0, TCSANOW, &g_sh.term);
			return ;
		}
		else if (ch == ';')
			flag = 1;
		else if ((ch >= '0' && ch <= '9') && flag == 0)
			*x = (*x * 10) + (ch - '0');
		else if ((ch >= '0' && ch <= '9') && flag == 1)
			*y = (*y * 10) + (ch - '0');
		else if (ch == 'R')
		{
			tcsetattr(0, TCSANOW, &g_sh.term);
			break ;
		}
	}
}

int		main(int ac, char **av, char **envp)
{
	int		ret;

	if (!ac || !av)
		return (-1);
	ret = ac;
	g_sh.envp = envp;
	set_env(envp);
	set_terminal();
	while (ret)
	{
		set_signal();
		init_config();
		set_prompt();
		set_process();
		/*
		 *while (env)
		 *{
		 *    printf("|%s|:|%s|\n", env->key, env->value);
		 *    env = env->next;
		 *}
		 */
		blt_intro();
		printf("here\n");
		hdoc_intro(); // segv
		free_conf(&g_sh);
	}
}
