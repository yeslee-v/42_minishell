#include "../../includes/minishell.h"

extern t_conf g_sh;

void	run_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	change_env_value("PWD", cwd, g_sh.env);
	free(cwd);
}
