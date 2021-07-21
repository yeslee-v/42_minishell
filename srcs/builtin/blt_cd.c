#include "../../includes/minishell.h"
#include <unistd.h>

void	run_cd(t_blt *blt, t_env *env)
{
	int		ret;
	char	buf[512];
	char	*home_val;
	char	*oldpwd_val;
	t_env	*env_tmp;

	if (blt->up_flag == 1)
		return ;
	// set oldpwd using search_env_key
	env_tmp = env;
	if (!(blt->args)) // $HOME
	{
		while (env_tmp)
		{
			if (!(ft_strncmp("HOME", env_tmp->key, 4)))
				home_val = env_tmp->value;
			env_tmp = env_tmp->next;
		}
		ret = chdir(home_val);
		if (ret == -1)
			printf("%s\n", strerror(errno));
		else if (!(ret))
			getcwd(buf, 512);
	}
	else // absolute or relative
	{
		ret = chdir(blt->args);
		if (ret == -1)
			printf("%s\n", strerror(errno));
		else if (!(ret))
			getcwd(buf, 512);
	}
}
