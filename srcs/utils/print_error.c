#include "../../includes/minishell.h"

extern t_conf g_sh;

void	print_status(int num, t_cmd *proc)
{
	if (num == 127)
	{
		if ((ft_strcmp(proc->cmd, "env") == 0) && (proc->arg))
			printf("%s: %s: %s\n", proc->cmd, proc->arg, NFD);
		else if (proc->arg)
			printf("%s: %s: %s\n", BS, proc->cmd, CNF);
		else
			printf("%s: %s: %s\n", BS, proc->cmd, CNF);
	}
	else if (num == 1)
	{
		if (proc->arg)
			printf("%s: %s: %s: %s\n", BS, proc->cmd, proc->arg, NFD);
		else
			printf("%s: %s: %s\n", BS, proc->cmd, NFD);
	}
}
