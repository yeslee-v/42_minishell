#include "../../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>

extern t_conf	g_sh;

int				is_blt(char *cmd)
{
	int	ret;

	ret = 0;
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

void			run_builtin(int num, t_cmd *proc, t_blt *blt)
{
	int redir = redir_init(proc);
	printf("redir is %d\n", redir);
	if ((redir == 1) && (num < 4))
	{
		printf("before blt g_sh is %d\n", g_sh.exit_status);
		printf("exit cmd is %s\n", proc->cmd);
		/*
			*g_sh.exit_status = 1;
			*/
		printf("after blt g_sh is %d\n", g_sh.exit_status);
		/*
		 *exit(1);
		 */
	}
	printf("prc is %s\n", proc->cmd);
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
	if (redir == 1)
		g_sh.exit_status = 1;
}

void			not_blt(t_cmd *proc)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = search_env_value("PATH", g_sh.env);
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		g_sh.exit_status = WEXITSTATUS(status);
		/*
		 *printf("not g: %d\n", g_sh.exit_status);
		 */
		return ;
		/*
		 *exit(WEXITSTATUS(status));
		 */
	}
	else if (pid == 0)
	{
		redir_init(proc);
		run_execve(proc);
	}
}

int				blt_intro(t_process *proc_lst)
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
	/*
	 *printf("ret is %d\n", ret);
	 */
	if (ret)
		run_builtin(ret, proc, &blt);
	else if (!ret)
		not_blt(proc);
	return (ret);
}
