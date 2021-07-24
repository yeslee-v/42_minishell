#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	first_fork(t_hdoc *hdoc)
{
	int		status;
	pid_t	pid;

	pid = fork();
	(void)hdoc;
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	/*else if (pid == 0)*/
		/*run_hdoc(hdoc);*/
	else
		write(2, "fork error\n", 11);
}

int		hdoc_intro()
{
	t_hdoc		hdoc;
	t_process	*proc;

	proc = g_sh.process->head;
	first_fork(&hdoc);
	return (0);
}
