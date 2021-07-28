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

void	run_execve(t_cmd *proc)
{
	int ret;

	ret = execve(proc->bin, (char *const *)proc->args, NULL);
	if (ret == -1)
		// error in cmd
		// 어떤 에러로 끝났는지 state에 저장된다 -> $? 에도 활용할 수 있음
		print_error("execve error");
}
