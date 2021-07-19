#include "../../includes/minishell.h"

void	run_cd(t_blt *blt, t_env *env)
{
	int		ret;
	char	buf[512];
	char	*home_val;

	if (blt->up_flag == 1)
		return ;
	else if (blt->args == NULL) // $HOME
	{
		while (env)
		{
			if (!(ft_strncmp("HOME", env->key, 4)))
				home_val = env->value;
			env = env->next;
		}
		ret = chdir(home_val);
		if (ret == -1)
			printf("%s\n", strerror(errno));
		else if (!(ret))
		{
			getcwd(buf, 512);
			printf("getcwd is |%s|\n", buf);
		}
	}
	else
	{
		ret = chdir(blt->args);
		if (ret == -1)
			printf("%s\n", strerror(errno));
		else if (!(ret))
		{
			getcwd(buf, 512);
			printf("path >> %s\n", buf);
		}
	}
}
