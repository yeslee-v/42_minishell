#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	relative_path(char *b_args, char buf[512])
{
	int		ret;
	char	*home_pwd;
	char	*abs_pwd;

	if ((b_args[0] == '~') && (b_args[1] == '/'))
	{
		home_pwd = search_env_value("HOME", g_sh.env);
		abs_pwd = ft_strjoin(home_pwd, (b_args + 1));
		b_args = abs_pwd;
	}
	ret = chdir(b_args);
	if (ret == -1)
	{
		g_sh.exit_status = 1;
		return ;
	}
	else if (!(ret))
		getcwd(buf, 512);
	change_env_value("PWD", buf, g_sh.env);
}

void	run_cd(char *b_args, t_blt *blt)
{
	int		ret;
	char	buf[512];
	t_env	*home;

	if (blt->up_flag == 1)
		return ;
	change_env_lst("PWD", "OLDPWD", g_sh.env);
	if (!(b_args) || (ft_strcmp("~", b_args)) == 0)
	{
		change_env_lst("HOME", "PWD", g_sh.env);
		home = search_env_node("HOME", g_sh.env);
		ret = chdir(home->value);
		if (ret == -1)
		{
			printf("here\n");
		}
		getcwd(buf, 512);
		change_env_value("PWD", buf, g_sh.env);
	}
	else
		relative_path(b_args, buf);
}
