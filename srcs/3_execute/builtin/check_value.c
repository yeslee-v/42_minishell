#include "../../../includes/minishell.h"

extern t_conf	g_sh;

int	check_args(char *b_args, t_cmd *proc)
{
	int	i;

	if (!(ft_isalpha(b_args[0]) || (b_args[0] == '_')))
	{
		g_sh.exit_status = 1;
		printf("%s: %s: `%s': %s\n", BS, proc->cmd, b_args, NVI);
		return (1);
	}
	i = 0;
	while (b_args[++i])
	{
		if (!(ft_isalpha(b_args[i]) || (b_args[i] == '_') || \
					ft_isdigit(b_args[i])))
		{
			g_sh.exit_status = 1;
			printf("%s: %s: `%s': %s\n", BS, proc->cmd, b_args, NVI);
			return (1);
		}
	}
	return (0);
}
