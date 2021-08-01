#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	exec_sig_handle(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	exit(130);
}

void	exec_sigquit(int signum)
{
	(void)signum;
	printf("Quit: 3\n");
	exit(131);
}

void	run_in_child(int i, int cnt, int *fd_prev, int fd_backup[2])
{
	return_terminal();
	signal(SIGINT, exec_sig_handle);
	signal(SIGQUIT, SIG_DFL);
	if (i > 0)
	{
		dup2(*fd_prev, STDIN);
		close(g_sh.pipe.fd[0]);
	}
	if (i < (cnt - 1))
		dup2(g_sh.pipe.fd[1], STDOUT);
	else
		dup2(fd_backup[1], STDOUT);
}

void	run_in_parents(int i, int cnt, int *fd_prev, t_cmd *proc)
{
	int	status;

	wait(&status);
	g_sh.exit_status = WEXITSTATUS(status);
	set_terminal();
	if (g_sh.exit_status)
	{
		if ((is_blt(proc->cmd) > 3) || (g_sh.exit_status == 127))
			print_status(WEXITSTATUS(status), proc);
	}
	if (!(WIFEXITED(status)))
		return ;
	if (i > 0)
		close(*fd_prev);
	*fd_prev = g_sh.pipe.fd[0];
	if (i == (cnt - 1))
		close(g_sh.pipe.fd[0]);
	close(g_sh.pipe.fd[1]);
}

void	run_pipe(int cnt, int fd_backup[2])
{
	int			i;
	int			fd_prev;
	t_cmd		*proc;
	t_process	*proc_lst;

	i = -1;
	proc_lst = g_sh.process->head;
	while (++i < cnt)
	{
		proc = proc_lst->cmd;
		if (i != (cnt - 1))
			pipe(g_sh.pipe.fd);
		set_all_redir_lst(proc_lst);
		g_sh.pipe.pid[i] = fork();
		if (g_sh.pipe.pid[i] > 0)
			run_in_parents(i, cnt, &fd_prev, proc);
		else if (g_sh.pipe.pid[i] == 0)
		{
			run_in_child(i, cnt, &fd_prev, fd_backup);
			blt_intro(proc_lst);
			exit(0);
		}
		else
			return ;
		proc_lst = proc_lst->next;
	}
}

void	pipe_intro(int cnt)
{
	int	fd_backup[2];

	g_sh.pipe.pid = malloc(sizeof(pid_t) * cnt);
	if (!(g_sh.pipe.pid))
		return ;
	fd_backup[0] = dup(0);
	fd_backup[1] = dup(1);
	run_pipe(cnt, fd_backup);
	dup2(fd_backup[0], 0);
	ft_free_single((void *)g_sh.pipe.pid);
}
