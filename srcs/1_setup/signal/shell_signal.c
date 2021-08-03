#include "../../../includes/minishell.h"

extern t_conf	g_sh;

void	sigint_handler(int signum)
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

void	sigquit_handler(int signum)
{
	int	size;

	size = ft_strlen(rl_line_buffer);
	if (signum == SIGQUIT)
	{
		if (size == 0)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		if (size != 0)
		{
			printf("\nQuit: 3\n");
			free_conf(&g_sh);
			free_env(g_sh.env);
			exit(131);
		}
	}
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
