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

void	run_execve(t_exec *exec)
{
	int	i;

	i = double_strlen(exec->cmd);
	printf("cmd is %s\n", exec->cmd[i]); // bin/ls
	printf("av is %s\n", (char *)exec->av); // ls -a
	printf("envp is %s\n", (char *)exec->envp); // NULL
	while (--i >= 0)
		execve(exec->cmd[i], exec->av, exec->envp);
	print_error("execve error");
}
