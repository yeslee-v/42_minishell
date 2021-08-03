#include "../../../includes/minishell.h"

extern t_conf	g_sh;

int	check_args(char *b_args, t_cmd *proc)
{
	int	i;

	if (!(ft_isalpha(b_args[0]) || (b_args[0] == '_')))
	{
		g_sh.exit_status = 1;
		print_status(g_sh.exit_status, proc);
		return (1);
	}
	i = 0;
	while (b_args[++i])
	{
		if (!(ft_isalpha(b_args[i]) || (b_args[i] == '_') || \
					ft_isdigit(b_args[i])))
		{
			g_sh.exit_status = 1;
			print_status(g_sh.exit_status, proc);
			return (1);
		}
	}
	return (0);
}

void	run_unset(char *b_args, t_cmd *proc, t_blt *blt)
{
	if ((blt->up_flag == 1) || !(b_args))
		return ;
	if (check_args(proc->arg, proc))
		return ;
	delete_env_node(b_args, g_sh.env);
}
