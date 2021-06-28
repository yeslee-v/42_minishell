#include "../include/pipe.h"

int		count_pipe(char **av)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (av[++i])
	{
		if (ft_strncmp(av[i], "|", 1))
			cnt++;
	}
	return (cnt);
}

void		allocate(int *args_num)
{
	int		i;

	i = -1;
	while (++i < *args_num)
	{
		if (!(pid->pid = malloc(*args_num + 1))) // child + parents
			return (0);
	}
}

int			main(int ac, char **av)
{
	int		p_cnt;
	int		status;
	int		args_num;
	t_all	all;

	p_cnt = count_pipe(av);
	args_num = p_cnt + 1;
	allocate(&args_num);
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1); // error in child process
	}
	else if (pid == 0)
	{
		pid[0] = fork();
	}
	else
		return (0);
	return (0);
}
