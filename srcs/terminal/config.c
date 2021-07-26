#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	set_term_cursor(void)
{
	struct termios	cursor;

	tcgetattr(0, &cursor);
	cursor.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &cursor);
}

int	set_term_default(int status)
{
	tcsetattr(0, TCSANOW, &g_sh.term);
	return (status);
}

void	set_terminal(void)
{
	tcgetattr(0, &g_sh.term);
	g_sh.term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &g_sh.term);
}
