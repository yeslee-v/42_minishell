#include "../../includes/minishell.h"

int		s_pipe_intro(int ac, char **av, char **path)
{
	pid_t	pid;
	t_exec	exec;
	int		status;

	if (ac != 5)
		print_error("The arguments are invalid");
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	else if (pid == 0)
		child_proc(av, path, &exec);
	else
		print_error("fork error");
	return (0);
}
