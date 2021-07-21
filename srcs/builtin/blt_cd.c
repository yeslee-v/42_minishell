#include "../../includes/minishell.h"
#include <unistd.h>

void	run_cd(t_blt *blt, t_env *env, t_lst *envl)
{
	int		ret;
	char	buf[512];
	t_env	*env_tmp;

	if (blt->up_flag == 1)
		return ;
	change_env_lst("PWD", "OLDPWD", envl);
	env_tmp = env;
	if (!(blt->args))
	{
		printf("here\n");
		change_env_lst("HOME", "PWD", envl);
	}
	else // absolute or relative
	{
		ret = chdir(blt->args);
		printf("ret is %d\n", ret);
		if (ret == -1)
			printf("%s\n", strerror(errno));
		else if (!(ret))
			getcwd(buf, 512);
		printf("path is |%s|\n", buf);
	}
}
