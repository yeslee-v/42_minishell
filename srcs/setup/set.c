/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkjaekwang <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 19:26:58 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/07/13 19:30:56 by parkjaekw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_conf g_sh;

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

char	**split_env(char *env)
{
	char	**ret;
	int		i;

	i = -1;
	if (!env)
		return (NULL);
	ret = malloc(sizeof(char *) * 3);
	while (env[++i])
	{
		if (env[i] == '=' && env[i + 1] != '\0')
		{
			ret[0] = ft_strrdup(env, 0, i - 1);
			ret[1] = ft_strrdup(env, i + 1, ft_strlen(env) - 1);
			ret[2] = NULL;
			break ;
		}
		else if (env[i] == '=' && env[i + 1] == '\0')
		{
			ret[0] = ft_strrdup(env, 0, i - 1);
			ret[1] = NULL;
			ret[2] = NULL;
			break ;
		}
	}
	return (ret);
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
	}
	g_sh.env = env;
}
