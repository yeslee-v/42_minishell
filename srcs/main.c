#include "../includes/minishell.h"

t_conf	g_sh;

int	main(int ac, char **av, char **envp)
{
	int	ret;

	if (!ac || !av)
		return (-1);
	ret = ac;
	g_sh.envp = envp;
	set_env(envp);
	set_terminal();
	while (ret)
	{
		set_signal();
		init_config();
		set_prompt();
		set_process();
		set_redirect();
		print_system();
		free_conf(&g_sh);
	}
}
