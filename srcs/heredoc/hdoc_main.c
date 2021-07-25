#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	first_fork(t_lst *i_redir)
{
	int		status;
	pid_t	pid;

	pid = fork();
	(void)i_redir;
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
	t_process	*proc;

	proc = g_sh.process->head;
	return (0);
}
