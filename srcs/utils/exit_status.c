#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			print_status(int num, t_cmd *proc)
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
			printf("%s: %s: %s: %s\n", BS, proc->cmd, proc->args[1], NFD);
		else
			printf("%s: %s: %s\n", BS, proc->cmd, NFD);
	}
}
