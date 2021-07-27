#include "../../includes/minishell.h"

extern t_conf	g_sh;

int	get_process_count(void)
{
	int			cnt;
	t_lst		*process;
	t_process	*node;

	cnt = 0;
	process = g_sh.process;
	node = process->head;
	while (node)
	{
		cnt++;
		node = node->next;
	}
	return (cnt);
}
