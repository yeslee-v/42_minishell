#include "../../includes/minishell.h"
#include <sys/wait.h>

extern t_conf	g_sh;

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

void			run_builtin(t_cmd *proc, t_blt *blt, t_lst *envl)
{
	int	num;
	int	ret;

	ret = 0;
	redir_init(proc);
	num = is_blt(proc->cmd);
	if (num == B_ECHO)
		run_echo(proc->arg, blt);
	else if (num == B_CD)
		run_cd(proc->arg, blt, envl);
	else if (num == B_PWD)
		run_pwd(envl);
	else if (num == B_EXPORT)
		run_export(proc->arg, blt, envl);
	else if (num == B_UNSET)
		run_unset(proc->arg, blt, envl);
	else if (num == B_ENV)
		run_env(0, envl);
	else
		ret = 127;
	exit(ret);
}

void			not_blt(t_cmd *proc, t_lst *envl)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = search_env_value("PATH", envl);
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		exit(WEXITSTATUS(status));
	}
	else if (pid == 0)
	{
		redir_init(proc);
		run_execve(proc);
	}
}

void	blt_intro(t_process *proc_lst)
{
	t_blt	blt;
	t_lst	*envl;
	t_cmd	*proc;
	int		ret;

	envl = g_sh.env;
	proc = proc_lst->cmd;
	init_blt(&blt);
	set_lower(proc->cmd, &blt);
	ret = is_blt(proc->cmd);
	if (ret)
		run_builtin(proc, &blt, envl);
	else if (!ret)
		not_blt(proc, envl);
}
