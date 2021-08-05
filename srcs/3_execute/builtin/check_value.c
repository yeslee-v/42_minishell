#include "../../../includes/minishell.h"

extern t_conf	g_sh;

void	print_error(char *b_args, t_cmd *proc)
{
	ft_putstr_fd("BraveShell: ", 2);
	ft_putstr_fd(proc->cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(b_args, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	check_args(char *b_args, t_cmd *proc)
{
	int	i;

	if (!(ft_isalpha(b_args[0]) || (b_args[0] == '_')))
	{
		g_sh.exit_status = 1;
		print_error(b_args, proc);
		return (1);
	}
	i = 0;
	while (b_args[++i])
	{
		if (!(ft_isalpha(b_args[i]) || (b_args[i] == '_') || \
					ft_isdigit(b_args[i])))
		{
			g_sh.exit_status = 1;
			print_error(b_args, proc);
			return (1);
		}
	}
	return (0);
}
