#include "../../includes/minishell.h"

void	alloc_fd(int cnt, t_all *all)
{
	int	i;

	i = -1;
	if (!(all->fd = (int **)malloc(sizeof(int *) * (cnt - 3))))
		print_error("malloc error"); // malloc invalid ?
	while (++i < cnt - 3)
		all->fd[i] = (int *)malloc(sizeof(int) * 2);
}

void	set_wait(void)
{
	int	status;

	wait(&status);
	if (!(WIFEXITED(status)))
		exit(status); // status includes error code in child process
}

void	ctrl_mid_cmd(int cnt, char **av, char *path, t_all *all)
{
	int	i;

	i = -1;
	while (++i < (cnt - 3)) // middle command
	{
		pipe(all->fd[i]);
		all->pid[i + 1] = fork();
		if (all->pid[i + 1] == 0) // child
		{
			split_path(av[i + 3], path, &all->exec);
			if (i != 0)
				run_dup2(0, all->fd[i - 1]); // std_in
			run_dup2(1, all->fd[i]);         // std_out
			close_fd(1, all->fd[i]);         // std_in
			run_execve(&all->exec);
		}
		else if (all->pid[i + 1] > 0) // parents
		{
			if (i != 0)
				close_fd(1, all->fd[i - 1]); // std_in
			close_fd(2, all->fd[i]);         // std_out
			set_wait();
		}
	}
}

void	middle_proc(int cnt, char **av, char *path, t_all *all)
{
	split_path(av[2], path, &all->exec); // for execve
	connect_in(av[1]);            // infile open + dup2 + close
	alloc_fd(cnt, all);
	ctrl_mid_cmd(cnt, av, path, all);
}
