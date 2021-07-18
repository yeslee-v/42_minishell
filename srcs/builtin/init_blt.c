#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			init_blt(t_blt *blt)
{
	blt->p_cmd = NULL;
	blt->opt = 0;
	blt->up_flag = 0;
	blt->args = NULL;
}

void			set_lower(t_blt *blt)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = blt->p_cmd;
	while (cmd[i])
	{
		if ((cmd[i] >= 65) && (cmd[i] <= 90))
		{
			cmd[i] += 32;
			blt->up_flag = 1;
		}
		i++;
	}
}

void			set_builtin(t_blt *blt, t_env *env)
{
	if (!(ft_strncmp(blt->p_cmd, "echo", ft_strlen(blt->p_cmd))))
		run_echo(blt);
	env = NULL;
	/*
	 *else if (!(ft_strncmp(blt->p_cmd, "cd", ft_strlen(blt->p_cmd))))
	 *    run_cd(env, blt);
	 *else if (!(ft_strncmp(blt->p_cmd, "pwd", ft_strlen(blt->p_cmd))))
	 *    run_pwd();
	 *else if (!(ft_strncmp(blt->p_cmd, "export", ft_strlen(blt->p_cmd))))
	 *    run_export(env, blt);
	 *else if (!(ft_strncmp(blt->p_cmd, "unset", ft_strlen(blt->p_cmd))))
	 *    run_unset(env, blt);
	 *else if (!(ft_strncmp(blt->p_cmd, "env", ft_strlen(blt->p_cmd))))
	 *    run_env(env);
	 *else if (!(ft_strncmp(blt->p_cmd, "exit", ft_strlen(blt->p_cmd))))
	 *    run_exit(blt);
	 */
}

int				blt_intro()
{
	t_blt		blt;
	t_process	*proc;
	t_syntax	*stx;
	t_env		*env;

	init_blt(&blt);
	env = g_sh.env->head;
	proc = g_sh.process->head;
	stx = proc->syntax->head;
	/*
		*while (env)
		*{
		*    printf("|%s|:|%s|\n", env->key, env->value);
		*    env = env->next;
		*}
		*/
	blt.p_cmd = stx->cmd;
	blt.args = stx->arg_line;
	set_lower(&blt);
	set_builtin(&blt, env);
	return (0);
}
