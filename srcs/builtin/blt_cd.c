#include "../../includes/minishell.h"

void	run_cd(t_blt *blt, t_env *env)
{
	int		ret;
	char	buf[512];
	char	*home_val;

	if (blt->up_flag == 1)
		return ;
	printf("\n========pwd======\n");
	print_env_value("PWD", env);
	printf("\n\n======oldpwd=======\n"); // not complete
	ret = chdir(blt->args);
	if (ret == -1)
		printf("%s\n", strerror(errno));
	else if (!(ret))
	{
		getcwd(buf, 512);
		printf("oldpwd >> %s\n", buf);
	}
	print_env_value("OLDPWD", env);
	if (!(blt->args)) // $HOME
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
			getcwd(buf, 512);
	}
	else
	{
		ret = chdir(blt->args);
		if (ret == -1)
			printf("%s\n", strerror(errno));
		else if (!(ret))
			getcwd(buf, 512);
	}
}
