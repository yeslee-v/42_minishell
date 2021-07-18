#include "../../includes/minishell.h"

void	parents_proc(char **av, char **path, t_exec *exec)
{
	int		status;

	wait(&status);
	if (!(WIFEXITED(status)))
		exit(1);
	split_path(av[3], path, exec);
	connect_out(av[4]);
	run_dup2(0, exec);
	close_fd(2, exec);
	run_execve(exec);
}

void	child_proc(char **av, char **path, t_exec *exec)
{
	int		pid;

	pipe(exec->fd);
	pid = fork();
	if (pid > 0)
		parents_proc(av, path, exec);
	else if (pid == 0)
	{
		split_path(av[2], path, exec);
		connect_in(av[1]);
		run_dup2(1, exec);
		close_fd(2, exec);
		run_execve(exec);
	}
	else
		print_error("fork error");
}
