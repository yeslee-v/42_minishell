#include "../../includes/minishell.h"
#include <sys/wait.h>

extern t_conf	g_sh;

int	is_blt(char *cmd)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		ret = 1;
	else if (ft_strcmp(cmd, "cd") == 0)
		ret = 2;
	else if (ft_strcmp(cmd, "pwd") == 0)
		ret = 3;
	else if (ft_strcmp(cmd, "export") == 0)
		ret = 4;
	else if (ft_strcmp(cmd, "unset") == 0)
		ret = 5;
	else if (ft_strcmp(cmd, "env") == 0)
		ret = 6;
	else if (ft_strcmp(cmd, "exit") == 0)
		ret = 7;
	return (ret);
}

void	run_builtin(t_cmd *proc, t_blt *blt)
{
	int	num;

	redir_init(proc);
	num = is_blt(proc->cmd);
	if (num == B_ECHO)
		run_echo(proc->arg, blt);
	else if (num == B_CD)
		run_cd(proc->arg, blt);
	else if (num == B_PWD)
		run_pwd();
	else if (num == B_EXPORT)
		run_export(proc->arg, blt);
	else if (num == B_UNSET)
		run_unset(proc->arg, blt);
	else if (num == B_ENV)
		run_env(0);
}

void	not_blt(t_cmd *proc)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = search_env_value("PATH", g_sh.env);
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

int	blt_intro(t_process *proc_lst)
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
		run_builtin(proc, &blt);
	else if (!ret)
		not_blt(proc);
	return (ret);
}
