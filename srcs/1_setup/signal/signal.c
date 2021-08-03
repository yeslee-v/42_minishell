#include "../../../includes/minishell.h"

extern t_conf	g_sh;

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("%d\n", rl_point);
		g_sh.exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signum)
{
	/*int size;*/

	/*if (signum == SIGQUIT)*/
	/*{*/
		/*size = ft_strlen(rl_line_buffer);*/
		/*rl_on_new_line();*/
	/*}*/
	if (signum == SIGQUIT)
	{
		printf("\nQuit: 3\n");
		exit(131);
	}
}

void	set_signal(void)
{
	int size;

	size = ft_strlen(rl_line_buffer);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (size > 0)
		signal(SIGQUIT, sigquit_handler);
}

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
	printf("\n");
	rl_on_new_line();
	exit(130);
}

void	exec_sigquit(int signum)
{
	(void)signum;
	printf("Quit: 3\n");
	exit(131);
}
