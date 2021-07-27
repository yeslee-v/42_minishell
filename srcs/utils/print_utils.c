#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	print_double_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("[arg][%d] = %s\n", i, str[i]);
		i++;
	}
}

void	print_system(void)
{
	printf("[lexical analysis]\n");
	printf("cmd = %s\nlex = %s\n", g_sh.cmd, g_sh.lexer->lex);
	printf("------------------\n");
	printf("[tokenizing]\n");
	print_token(g_sh.token);
	printf("------------------\n");
	printf(RED"[parsing]\n"RESET);
	print_process(g_sh.process);
	printf(CYAN"---------------------------------------------\n"RESET);
}
