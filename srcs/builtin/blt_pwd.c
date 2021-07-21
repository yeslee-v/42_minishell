#include "../../includes/minishell.h"

void	run_pwd(t_lst *envl)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	change_env_value("PWD", cwd, envl);
	free(cwd);
}
