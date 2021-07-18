/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 20:30:39 by jaekpark          #+#    #+#             */
/*   Updated: 2021/07/18 16:22:16 by yeslee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_conf	g_sh;

int		main(int ac, char **av, char **envp)
{
	int	ret;

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
