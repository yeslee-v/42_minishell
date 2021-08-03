#include "../../../includes/minishell.h"

extern t_conf	g_sh;

int	is_cmd(char *dest, char *src)
{
	if (ft_strcmp(dest, src) == 0)
		return (1);
	return (0);
}

void	print_status(int num, t_cmd *proc)
{
	if (!(proc->cmd))
		return ;
	else if (num == 127)
	{
		if (proc->arg)
			printf("%s: %s: %s\n", BS, proc->cmd, CNF);
		else
			printf("%s: %s: %s\n", BS, proc->cmd, CNF);
	}
	else if (num == 1)
	{
		if (proc->arg)
		{
			if (is_cmd(proc->cmd, "export") || is_cmd(proc->cmd, "unset"))
				printf("%s: %s: `%s': %s\n", BS, proc->cmd, proc->args[1], NVI);
			else
				printf("%s: %s: %s: %s\n", BS, proc->cmd, proc->args[1], NFD);
		}
		else
			printf("%s: %s: %s\n", BS, proc->cmd, NFD);
	}
}
