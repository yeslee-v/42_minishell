#include "../includes/pipe.h"

void		alloc_fd(int args_cnt, t_all *all)
{
	int		i;
	
	i = -1;
	if (!(all->fd = (int **)malloc(sizeof(int *) * (args_cnt - 3))))
		print_error("malloc error"); // malloc invalid ?
	while (++i < args_cnt - 3)
		all->fd[i] = (int *)malloc(sizeof(int) * 2);
}

void		set_wait(void)
{
	int		status;

	wait(&status);
	if (!(WIFEXITED(status)))
		exit(status); // error in child process
}

int		middle_proc(int args_cnt, char **av, char **path, t_all *all)
{
	int	i;

	split_path(av[2], path, all); // for execve
	connect_in(av[1]); // infile open + dup2 + close
	alloc_fd(args_cnt, all);
	i = -1;
	while (++i < (args_cnt - 3)) // middle command
	{
		pipe(all->fd[i]);
		all->pid[i + 1] = fork();
		if (all->pid[i + 1] == 0) // child
		{
			split_path(av[i + 3], path, all);
			if (i != 0)
				run_dup2(0, all->fd[i - 1]);//std_in
			run_dup2(1, all->fd[i]); //std_out
			close_fd(1, all->fd[i]); //std_in
			run_execve(all);
		}
		else if (all->pid[i + 1] > 0) // parents
		{
			if (i != 0)
				close_fd(1, all->fd[i - 1]); //std_in
			close_fd(2, all->fd[i]); //std_out
			set_wait();
		}
	}
	return (i);
}

int			main(int ac, char **av, char **path)
{
	int		i;
	int		args_cnt;
	t_all	all;

	i = 0;
	args_cnt = ac - 1;
	if (!(all.pid = malloc(sizeof(pid_t) * args_cnt)))
		return (0);
	all.pid[0] = fork();
	if (all.pid[0] > 0) // grand
		set_wait();
	else if (all.pid[0] == 0) // parents or child
	{
		i = middle_proc(args_cnt, av, path, &all);
		run_dup2(0, all.fd[i - 1]);
		split_path(av[args_cnt - 1], path, &all);
		connect_out(av[args_cnt]);
		run_execve(&all);
	}
	else
		print_error("fork error");
	return (0);
}
