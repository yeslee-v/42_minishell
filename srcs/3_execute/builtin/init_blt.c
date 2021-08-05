#include "../../../includes/minishell.h"

extern t_conf	g_sh;

int	is_blt(char *cmd)
{
	int	ret;

	ret = 0;
	if (!cmd)
		return (-1);
	if (ft_strcmp(cmd, "echo") == 0)
		ret = B_ECHO;
	else if (ft_strcmp(cmd, "env") == 0)
		ret = B_ENV;
	else if (ft_strcmp(cmd, "pwd") == 0)
		ret = B_PWD;
	else if (ft_strcmp(cmd, "export") == 0)
		ret = B_EXPORT;
	else if (ft_strcmp(cmd, "unset") == 0)
		ret = B_UNSET;
	else if (ft_strcmp(cmd, "cd") == 0)
		ret = B_CD;
	else if (ft_strcmp(cmd, "exit") == 0)
		ret = B_EXIT;
	return (ret);
}

void	run_builtin(int num, t_process *proc_lst, t_blt *blt)
{
	int	redir;

	if (proc_lst->redir_err == 1)
		return ;
	redir = redir_init(proc_lst->cmd);
	if (redir == 1)
	{
		g_sh.exit_status = 1;
		return ;
	}
	if (num == B_ECHO)
		run_echo(proc_lst->cmd, blt);
	else if (num == B_CD)
		run_cd(proc_lst->cmd->arg, blt);
	else if (num == B_PWD)
		run_pwd();
	else if (num == B_EXPORT)
		run_export(proc_lst->cmd, blt);
	else if (num == B_UNSET)
		run_unset(proc_lst->cmd->args, blt);
	else if (num == B_ENV)
		run_env(0, proc_lst->cmd);
	else if (num == B_EXIT)
		run_exit(proc_lst->cmd->args);
}

void	not_blt(t_cmd *proc)
{	
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		g_sh.exit_status = WEXITSTATUS(status);
		return ;
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
	redir_in_pipe(proc_lst);
	ret = is_blt(proc->cmd);
	if (ret)
		run_builtin(ret, proc_lst, &blt);
	else if (!ret)
		not_blt(proc);
	return (ret);
}
