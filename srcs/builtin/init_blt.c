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

void			set_builtin(char **all_env, t_blt *blt, t_env *env, t_lst *envl)
{
	if (!(ft_strncmp(blt->p_cmd, "echo", ft_strlen(blt->p_cmd))))
		run_echo(blt, env);
	else if (!(ft_strncmp(blt->p_cmd, "cd", ft_strlen(blt->p_cmd))))
		run_cd(blt, env, envl);
	else if (!(ft_strncmp(blt->p_cmd, "pwd", ft_strlen(blt->p_cmd))))
		run_pwd(envl);
	else if (!(ft_strncmp(blt->p_cmd, "export", ft_strlen(blt->p_cmd))))
		run_export(blt, envl);
	else if (!(ft_strncmp(blt->p_cmd, "unset", ft_strlen(blt->p_cmd))))
		run_unset(all_env, blt, env, envl);
	else if (!(ft_strncmp(blt->p_cmd, "env", ft_strlen(blt->p_cmd))))
		run_env(0, envl);
}

int				blt_intro()
{
	t_blt		blt;
	t_process	*proc;
	t_syntax	*stx;
	t_env		*env;
	t_lst		*envl;
	char		**all_env;

	init_blt(&blt);
	all_env = g_sh.envp;
	env = g_sh.env->head;
	proc = g_sh.process->head;
	stx = proc->syntax->head;
	blt.p_cmd = stx->cmd;
	blt.args = stx->arg_line;
	envl = g_sh.env;
	set_lower(&blt);
	set_builtin(all_env, &blt, env, envl);
	return (0);
}
