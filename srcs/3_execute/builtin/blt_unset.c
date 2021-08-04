#include "../../../includes/minishell.h"

extern t_conf	g_sh;

static void	unset_error(char *arg)
{
	ft_putstr_fd("BraveShell: unset: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("not a valid identifier\n", 1);
}

static int	env_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

static int	check_valid_arg(char *arg)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	if (!arg)
		return (-1);
	ret = check_valid_char(arg[0]);
	if (ret != 1)
		return (-1);
	while (arg[++i])
	{
		if ((env_char(arg[i])) == 0)
			return (-1);
	}
	return (1);
}

static int	check_args(char **args)
{
	int	i;
	int	valid;
	int	ret;

	i = 0;
	ret = 0;
	valid = 1;
	if (!args)
		return (-1);
	while (args[++i])
	{
		valid = check_valid_arg(args[i]);
		if (valid == -1)
		{
			unset_error(args[i]);
			ret = -1;
		}
		else
			delete_env_node(args[i], g_sh.env);
	}
	return (ret);
}

void	run_unset(char **args, t_blt *blt)
{
	int	size;
	int	ret;

	ret = 0;
	if (!args)
		return ;
	size = ft_double_strlen((const char **)args);
	if (size <= 1 || (blt->up_flag == 1))
		return ;
	ret = check_args(args);
	if (ret == -1)
		g_sh.exit_status = 1;
}
