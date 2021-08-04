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

void	execute_command(t_process *node)
{
	int	process;
	int	builtin;

	builtin = 0;
	if (!node || !node->cmd)
		return ;
	process = get_process_count();
	if (process == 1)
		builtin = is_blt(node->cmd->cmd);
	if (builtin > 3)
	{
		g_sh.col = 12;
		blt_intro(node);
		dup2(g_sh.fd_backup[0], READ);
		dup2(g_sh.fd_backup[1], WRITE);
	}
	else
		pipe_intro(process);
}

void	calc_cursor(t_process *node)
{
	int	builtin;
	t_blt blt;
	int ret;

	ret = 0;
	if (!node || !node->cmd || !node->cmd->cmd)
		return ;
	builtin = 0;
	init_blt(&blt);
	builtin = is_blt(node->cmd->cmd);
	if (builtin == B_ECHO)
		ret = calc_echo(node->cmd, &blt);
	g_sh.col = 12 + ret;
}

int	main(int ac, char **av, char **envp)
{
	int			ret;
	t_process	*node;

	if (!ac || !av)
		return (-1);
	set_default_config(envp);
	g_sh.col = 12;
	while (1)
	{
		ret = set_minishell();
		if (ret != 1)
		{
			analyze_command();
			node = g_sh.process->tail;
			calc_cursor(node);
			execute_command(g_sh.process->head);
		}
		free_conf(&g_sh);
	}
	free_env(g_sh.env);
}
