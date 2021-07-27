#include "../../includes/minishell.h"

extern t_conf g_sh;

int		double_strlen(const char **str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

void	run_execve()
{
	int	i;

	printf("cmd is %s\n", g_sh.exec.cmd[0]);
	printf("av is %s\n", (char *const)g_sh.exec.av[0]);
	printf("envp is %s\n", (char *const)g_sh.exec.envp);
	i = double_strlen(g_sh.exec.cmd);
	while (--i >= 0)
		execve(g_sh.exec.cmd[i], g_sh.exec.av, g_sh.exec.envp);
	// error in cmd
	// 어떤 에러로 끝났는지 state에 저장된다 -> $? 에도 활용할 수 있음
	print_error("execve error");
}
