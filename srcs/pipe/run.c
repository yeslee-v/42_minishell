#include "../../includes/minishell.h"

extern t_conf g_sh;

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

void	run_execve(t_cmd *proc)
{
	execve(proc->bin, (char *const *)proc->args, g_sh.envp);
	exit(127);
}
