#include "../includes/minishell.h"

t_conf	g_sh;

int	set_default_config(char **envp)
{
	if (!envp)
		return (0);
	g_sh.envp = envp;
	set_env(envp);
	g_sh.exit_status = 0;
	set_terminal();
	return (1);
}

int	set_minishell(void)
{
	int	ret;

	ret = 0;
	set_signal();
	init_config();
	set_prompt();
	set_process();
	ret = set_redirect(g_sh.process);
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	int			ret;
	int			proc_cnt;
	t_process	*proc_lst;
	t_cmd		*proc;
	int			num;

	if (!ac || !av)
		return (-1);
	set_default_config(envp);
	while (1)
	{
		ret = set_minishell();
		if (g_sh.process->head != NULL)
		{
			proc_lst = g_sh.process->head;
			proc = proc_lst->cmd;
		}
		if (ret != 1 && proc != NULL)
		{
			analyze_command();
			proc_cnt = get_process_count();
			num = is_blt(proc->cmd);
			if (proc_cnt == 1 && (num > 3))
			{
				blt_intro(proc_lst);
				if (g_sh.exit_status)
					print_status(g_sh.exit_status, proc);
				dup2(g_sh.fd_backup[0], READ);
				dup2(g_sh.fd_backup[1], WRITE);
			}
			else
				pipe_intro(proc_cnt);
		}
		/*
		 *print_system();
		 */
		free_conf(&g_sh);
	}
	free_env(g_sh.env);
}
