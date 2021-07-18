#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	first_fork(t_hdoc *hdoc, t_syntax *stx)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	else if (pid == 0)
		run_hdoc(hdoc, stx);
	else
		write(2, "fork error\n", 11);
}

int		hdoc_intro()
{
	t_hdoc		hdoc;
	t_process	*proc;
	t_syntax	*stx;

	proc = g_sh.process->head;
	stx = proc->syntax->head;
	hdoc.delimiter = stx->next->arg_line;
	first_fork(&hdoc, stx);
	return (0);
}
