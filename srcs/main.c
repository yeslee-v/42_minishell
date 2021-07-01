#include "../includes/minishell.h"
#include <readline/readline.h>

t_conf	g_sh;

int  ft_isspace(int c)
{
	if ((char)c == ' ')
		return (1);
	else if ((char)c == '\t')
		return (2);
	else if ((char)c == '\v')
		return (3);
	else if ((char)c == '\n')
		return (4);
	else if ((char)c == '\f')
		return (5);
	else if ((char)c == '\r')
		return (6);
	return (0);
}

char *ft_strrdup(char *s, int st, int ed)
{
	int i;
	char *ret;
	int dst_len;
	int src_len;

	i = 0;
	dst_len = ed - st + 1;
	src_len = ft_strlen(s);
	if (!s || dst_len > src_len)
		return (NULL);
	ret = malloc(sizeof(char) * dst_len + 1);
	while (st <= ed)
	{
		ret[i] = s[st];
		i++;
		st++;
	}
	ret[i] = '\0';
	return (ret);
}

int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	exit_shell(int num)
{
	printf("Good bye ~ !\n");
	exit(num);
}

void	test_print(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int print_prompt(void)
{
	g_sh.cmd = readline(PROMPT);
	add_history(g_sh.cmd);
	return (1);
}

void sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("" , 0);
		rl_redisplay();
	}
}

int ft_puta(int tc)
{
	ft_putchar_fd(tc, 1);
	return (0);
}


void get_cursor_position(int *col, int *rows)
{
	char buf[255];
	int ret = 0;
	int i = 1;
	int a = 0;
	int temp = 0;

	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = ft_atoi(&buf[i]) - 1;
			else
			{
				temp = ft_atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;	
	}
}

void eof_handler(void)
{
	int col;
	int rows;

	col = 0;
	rows = 0;
	get_cursor_position(&col, &rows);
	/*char *cm = tgetstr("cm", NULL);*/
	/*char *s = tgoto(cm, col, rows);*/
	/*tputs(s, 1, ft_puta);*/
	printf("%d %d\n", col, rows);
	exit(0);
}

/*t_token 	*make_token(char *token, char type)*/
/*{*/
	/*t_token *ret;*/

	/*ret = malloc(sizeof(t_token));*/
	/*ret->token*/
/*}*/

void	make_lst(t_lst *lst)
{
	if (lst == NULL)
	{
		lst = malloc(sizeof(t_lst));
		lst->head = NULL;
		lst->tail = NULL;
	}
}

void	lexer(void)
{
	int i;
	int space;
	char *white;
	char *tmp;

	i = 0;
	space = 0;
	tmp = ft_strdup(g_sh.cmd);
	ft_memset(tmp, 0, ft_strlen(tmp));
	while (g_sh.cmd[i])
	{
		if ((ft_isalpha(g_sh.cmd[i])) == 1)
			tmp[i] = 'c';
		else if ((ft_isnum(g_sh.cmd[i])) == 1)
			tmp[i] = 'n';
		else if ((space = ft_isspace(g_sh.cmd[i])) >= 1)
		{
			white = ft_itoa(space);
			tmp[i] = white[0];
		}
		else
			tmp[i] = g_sh.cmd[i];
		i++;
	}
	g_sh.lex = tmp;
}

int		main(int ac, char **av, char **envp)
{
	int	ret;

	(void)av;
	ret = ac;
	g_sh.env = envp;
	tcgetattr(0, &g_sh.term);
	g_sh.term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &g_sh.term);
	while (ret)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		print_prompt();
		if (g_sh.cmd == NULL)
			eof_handler();
		if ((ft_strcmp(g_sh.cmd, "exit")) == 0)
		{
			free(g_sh.cmd);
			exit_shell(0);
		}
		add_history(g_sh.cmd);
		rl_redisplay();
		lexer();
		printf("prompt = %s\nlexer = %s\n", g_sh.cmd, g_sh.lex);
		free(g_sh.cmd);
		free(g_sh.lex);
	}
}
