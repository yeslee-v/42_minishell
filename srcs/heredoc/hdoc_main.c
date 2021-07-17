#include "../../includes/minishell.h"

t_conf	g_sh;

int	intro_hdoc()
{
	int		status;
	pid_t	pid;
	t_hdoc	hdoc;

	hdoc_init(&hdoc);
	/*
	 *hdoc.delimiter = av[1]; // will changed
	 */
	hdoc.delimiter = "hi"; // will changed
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	else if (pid == 0)
		run_hdoc(&hdoc);
	else
		write(2, "fork error\n", 11);
	return (0);
}
