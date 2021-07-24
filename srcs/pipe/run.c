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
	while (--i >= 0)
		execve(exec->cmd[i], exec->av, exec->envp);
	// error in cmd
	// 어떤 에러로 끝났는지 state에 저장된다 -> $? 에도 활용할 수 있음
	print_error("execve error");
}
