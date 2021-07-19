#include "../../includes/minishell.h"

int		double_strlen(const char **str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

void	run_execve(t_all *all)
{
	int	i;

	i = double_strlen(all->exec.cmd);
	while (--i >= 0)
	{
		execve(all->exec.cmd[i], all->exec.av, all->exec.envp);
	}
	print_error("execve error");
}
