#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_conf		g_sh;

void		test_print(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n",1);
		i++;
	}
}

void		print_prompt(t_conf *conf)
{
	if (!conf)
	conf->cmd = readline(PROMPT);
}

int main(int ac, char **av, char **envp)
{
	int ret;

	ret = 1;
	g_sh.env = envp;
	test_print(g_sh.env);
	while(ret)
	{
		if ((signal(SIGQUIT, SIG_DFL)) = -1)
			
		print_prompt(&g_sh);
	}
}
