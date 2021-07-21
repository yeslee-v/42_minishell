#include "../../includes/minishell.h"

void	run_pwd(t_lst *envl)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	printf("cwd is %s\n", cwd);
	change_env_value("PWD", cwd, envl);
	printf("%s\n", cwd);
	free(cwd);
}
