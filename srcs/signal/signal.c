#include "../../includes/minishell.h"

extern t_conf	g_sh;

int	print_tc(int tc)
{
	write(1, &tc, 1);
	return (1);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sh.exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigusr1_handler(int signum)
{
	(void)signum;
	g_sh.exit_status = 1;
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, sigusr1_handler);
}
