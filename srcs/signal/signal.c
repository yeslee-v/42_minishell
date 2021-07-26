#include "../../includes/minishell.h"

extern t_conf	g_sh;

int		print_tc(int tc)
{
	write(1, &tc, 1);
	return (1);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_eof(void)
{
	int x;
	int y;
	char *cm;
	char *ce;

	x = 0;
	y = 0;
	get_cursor_pos(&x, &y);
	tgetent(NULL, "xterm");
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
	tputs(tgoto(cm, y + 11, x - 2), 1, print_tc);
	printf("exit\n");
	free_lexer(g_sh.lexer);
	free_token(g_sh.token);
	free_process(g_sh.process);
	exit(0);
}
