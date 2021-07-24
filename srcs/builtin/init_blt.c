#include "../../includes/minishell.h"
#include <sys/wait.h>

extern t_conf	g_sh;

void			init_blt(t_blt *blt)
{
	blt->opt = 0;
	blt->up_flag = 0;
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

int				is_blt(char *cmd)
{
	int	ret;

	ret = 0;
	if (!(ft_strcmp(cmd, "echo")))
		ret = 1;
	else if (!(ft_strcmp(cmd, "cd")))
		ret = 2;
	else if (!(ft_strcmp(cmd, "pwd")))
		ret = 3;
	else if (!(ft_strcmp(cmd, "export")))
		ret = 4;
	else if (!(ft_strcmp(cmd, "unset")))
		ret = 5;
	else if (!(ft_strcmp(cmd, "env")))
		ret = 6;
	return (ret);
}

void			run_builtin(char *cmd, char *b_args, t_blt *blt, t_env *env, t_lst *envl)
{
	int	num;

	num = is_blt(cmd);
	if (num == B_ECHO)
		run_echo(b_args, blt, env);
	else if (num == B_CD)
		run_cd(b_args, blt, envl);
	else if (num == B_PWD)
		run_pwd(envl);
	else if (num == B_EXPORT)
		run_export(b_args, blt, envl);
	else if (num == B_UNSET)
		run_unset(b_args, blt, envl);
	else if (num == B_ENV)
		run_env(0, envl);
	else
		return ;
}

void			not_blt(char *cmd, t_exec *exec, t_lst *envl)
{
	pid_t	pid;
	int		status;
	char		*path;

	path = search_env_value("PATH", envl);
	pid = fork();
	if (pid > 0)
	{
		wait(&status); // only one child(for execve) -> not use waitpid(pid, &status, 0)
		if (!(WIFEXITED(status)))
			exit(1); // child not success
	}
	else if (pid == 0)
	{
		split_path(cmd, path, exec);
		run_execve(exec);
	}
}

void			blt_intro(char *cmd, char *b_args)
{
	t_blt		blt;
	t_env		*env;
	t_lst		*envl;
	t_exec		exec;
	int			ret;

	printf("cmd is %s | b_args is %s\n", cmd, b_args);
	env = g_sh.env->head;
	envl = g_sh.env;
	init_blt(&blt);
	set_lower(&blt);
	ret = is_blt(cmd);
	if (ret)
		run_builtin(cmd, b_args, &blt, env, envl);
	else if (!ret)
		not_blt(cmd, &exec, envl);
}
