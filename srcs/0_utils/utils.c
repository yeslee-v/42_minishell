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

void	remove_hdoc(int i)
{
	char	*hdoc;
	char	*num;
	char	*file;

	hdoc = ft_strdup(".hdoc");
	num = ft_itoa(i);
	file = ft_strcjoin(hdoc, num, '_');
	unlink(file);
	if (num)
		free(num);
	if (file)
		free(file);
}
