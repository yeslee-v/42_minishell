#include "../../../includes/minishell.h"

extern t_conf	g_sh;

int	double_strlen(const char **str)
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
	if (!(proc->bin))
	{
		ft_putstr_fd("BraveShell: ", 2);
		ft_putstr_fd(proc->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(proc->bin, (char *const *)proc->args, g_sh.envp);
}
