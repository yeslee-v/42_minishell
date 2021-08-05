#include "../../../includes/minishell.h"

void	hdoc_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		exit(1);
	}
}

void	exec_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	exit(130);
}

void	exec_sigquit(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit: 3\n", 2);
	exit(131);
}
