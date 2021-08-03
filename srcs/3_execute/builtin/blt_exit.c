#include "../../../includes/minishell.h"

extern t_conf	g_sh;

static void	exit_argc_error(void)
{
	ft_putstr_fd("BraveShell: exit: too many arguments\n", 2);
	g_sh.exit_status = 1;
}

static void	exit_numeric_error(char *arg)
{
	ft_putstr_fd("BraveShell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_sh.exit_status = 255;
	exit(255);
}

static void	exit_with_arg(char *arg)
{
	int	exit_status;

	exit_status = 0;
	if (arg != NULL)
		exit_status = ft_atoi(arg);
	else
		exit_numeric_error(arg);
	g_sh.exit_status = (unsigned char)exit_status;
	exit(exit_status);
}

void	run_exit(char **args)
{
	int	exit_status;
	int	size;

	if (!args)
		return ;
	exit_status = 0;
	size = ft_double_strlen((const char **)args);
	ft_putstr_fd("exit\n", 1);
	if (size >= 3)
	{
		if ((ft_strnum(args[1])) == 1)
			exit_argc_error();
		else
			exit_numeric_error(args[1]);
	}
	else if (size == 2)
		exit_with_arg(args[1]);
	else
		exit(0);
}
