#include "../../includes/minishell.h"

void	relative_path(char *b_args, char buf[512], t_lst *envl)
{
	int		ret;
	char	*home_pwd;
	char	*abs_pwd;

	if ((b_args[0] == '~') && (b_args[1] == '/'))
	{
		home_pwd = search_env_value("HOME", envl);
		abs_pwd = ft_strjoin(home_pwd, (b_args + 1));
		b_args = abs_pwd;
	}
	ret = chdir(b_args);
	if (ret == -1)
		printf("%s\n", strerror(errno));
	else if (!(ret))
		getcwd(buf, 512);
	change_env_value("PWD", buf, envl);
}

void	run_cd(char *b_args, t_blt *blt, t_lst *envl)
{
	int		ret;
	char	buf[512];
	t_env	*home;

	if (blt->up_flag == 1)
		return ;
	change_env_lst("PWD", "OLDPWD", envl);
	if (!(b_args) || (ft_strcmp("~", b_args)) == 0)
	{
		change_env_lst("HOME", "PWD", envl);
		home = search_env_node("HOME", envl);
		ret = chdir(home->value);
		if (ret == -1)
			printf("%s\n", strerror(errno));
		getcwd(buf, 512);
		change_env_value("PWD", buf, envl);
	}
	else
		relative_path(b_args, buf, envl);
}
