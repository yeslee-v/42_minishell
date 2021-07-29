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

	printf("redir is %s|%s|%d\n", proc->input_redir, proc->output_redir, proc->append);
	if (proc->input_redir)
	{
		printf("input is %s\n", proc->input_redir);
		
	}
	if (proc->output_redir)
	{
		printf("output is %s\n", proc->output_redir);
	}
	if (proc->append)
	{
		printf("append is %d\n", proc->append);
/*
 *        if (!(proc->append))
 *        {
 *
 *        }
 *        else if (proc->append == 1)
 *        {
 *            // output_redir
 *        }
 */

	}
	ret = execve(proc->bin, (char *const *)proc->args, NULL);
	if (ret == -1) // error in cmd
		print_error("execve error");
}
