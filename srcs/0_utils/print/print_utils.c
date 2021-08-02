#include "../../../includes/minishell.h"

extern t_conf	g_sh;

void	print_double_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		printf("[arg][%d] = %s\n", i, str[i]);
		i++;
	}
}

void	print_system(void)
{
	printf(B_WHITE"----------------------------------------------\n"RESET);
	printf(B_CYAN"[입력 커맨드 어휘 분석]\n"RESET);
	printf(B_PURPLE"> 쉘 프롬포트에서 입력받은 커맨드\n"RESET);
	if (g_sh.cmd != NULL && g_sh.lexer != NULL)
		printf(GREEN"  o [커맨드] = %s\n"BLUE"  o [인덱싱] = %s\n"RESET, g_sh.cmd, g_sh.lexer->lex);
	else
		printf("  o -\n");
	printf(B_WHITE"----------------------------------------------\n"RESET);
	printf(B_WHITE"\n----------------------------------------------\n"RESET);
	printf(B_CYAN"[토크나이징]\n"RESET);
	print_token(g_sh.token);
	printf(B_WHITE"----------------------------------------------\n"RESET);
	printf(B_WHITE"\n----------------------------------------------\n"RESET);
	printf(B_CYAN"[파싱]\n"RESET);
	print_process(g_sh.process);
	printf(B_WHITE"----------------------------------------------\n"RESET);
}
