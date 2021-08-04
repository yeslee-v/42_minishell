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
	if (!(proc->bin) || (proc->cmd && proc->cmd[0] == '\0'))
	{
		ft_putstr_fd("BraveShell: ", 2);
		ft_putstr_fd(proc->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(proc->bin, (char *const *)proc->args, g_sh.envp);
	if (errno != 0)
	{
		ft_putstr_fd("BraveShell: ", 2);
		ft_putstr_fd(proc->bin, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
}
