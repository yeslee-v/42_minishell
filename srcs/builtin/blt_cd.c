#include "../../includes/minishell.h"

void	run_cd(t_blt *blt, t_env *env, t_lst *envl)
{
	int		ret;
	char	buf[512];
	t_env	*env_tmp;
	t_env	*home;
	char	*home_pwd;
	char	*abs_pwd;

	if (blt->up_flag == 1)
		return ;
	change_env_lst("PWD", "OLDPWD", envl);
	env_tmp = env;
	if (!(blt->args) || (ft_strcmp("~", blt->args)) == 0)
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
	{
		if ((blt->args[0] == '~') && (blt->args[1] == '/'))
		{
			home_pwd = search_env_value("HOME", envl);
			abs_pwd = ft_strjoin(home_pwd, (blt->args + 1));
			blt->args = abs_pwd;
		}
		ret = chdir(blt->args);
		if (ret == -1)
			printf("%s\n", strerror(errno));
		else if (!(ret))
			getcwd(buf, 512);
		change_env_value("PWD", buf, envl);
	}
}
