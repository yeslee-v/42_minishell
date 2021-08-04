#include "../../../includes/minishell.h"

extern t_conf	g_sh;

static void	init_pos(int *x, int *y)
{
	*x = 0;
	*y = 0;
}

static int	print_tc(int tc)
{
	write(0, &tc, 1);
	return (1);
}

int	get_cursor_pos(int *x, int *y)
{
	int		ret;
	int		flag;
	char	buf[255];
	char	ch;
	int i;	
	int		cnt;

	flag = 0;
	i = 0;
	init_pos(x, y);
	set_term_cursor();
	write(0, "\033[6n", 4);
	cnt = read(0, buf, 255);
	buf[cnt] = '\0';
	while (buf[i])
	{
		if (buf[i] == 'R')
			return (set_term_default(0));
		else if (buf[i] == ';')
			flag = 1;
		else if ((buf[i] >= '0' && buf[i] <= '9') && flag == 0)
			*x = (*x * 10) + (buf[i] - '0');
		else if ((buf[i] >= '0' && buf[i] <= '9') && flag == 1)
			*y = (*y * 10) + (buf[i] - '0');
		i++;
	}
	return (set_term_default(1));
}

void	move_cursor(char *msg, int col, int row)
{
	int		x;
	int		y;
	char	*cm;
	char	*sc;
	char	*rc;

	x = 0;
	y = 0;
	get_cursor_pos(&x, &y);
	tgetent(NULL, getenv("TERM"));
	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, y + col, x - row), 0, print_tc);
	if (msg)
		printf("%s", msg);
}
