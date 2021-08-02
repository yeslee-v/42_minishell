#include "../includes/minishell.h"

t_conf	g_sh;

int		set_default_config(char **envp)
{
	if (!envp)
		return (0);
	g_sh.envp = envp;
	g_sh.exit_status = 0;
	set_terminal();
	return (1);
}

int		set_minishell(char **envp)
{
	int	ret;

	ret = 0;
	set_env(envp);
	set_signal();
	init_config();
	set_prompt();
	set_process();
	ret = set_redirect(g_sh.process);
	return (ret);
}

void	test_exec(t_process *node)
{
	int		pid;
	int		status;
	t_cmd	*tmp;

	tmp = node->cmd;
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
	}
	if (pid == 0)
	{
		execve(tmp->bin, tmp->args, g_sh.envp);
		if (errno != 0)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(0);
		}
	}
}

int		main(int ac, char **av, char **envp)
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
		ret = set_minishell(envp);
		if (g_sh.process->head != NULL)
		{
			proc_lst = g_sh.process->head;
			proc = proc_lst->cmd;
		}
		if (ret != 1 || proc != NULL)
		{
			analyze_cmd();
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
		/*print_system();*/
		free_conf(&g_sh);
	}
}

/*
 *ret == 1 인 경우 heredoc에서 인터럽트 발생 -> 바로 메모리 해제하고
 *다시 프롬포트 함수로이동-> g_sh.exit_status = 1
 *ret != 1 인경우 정상 실행 빌트인 or EXEC program
 */

/*
 *
 *t_prcoess *node;
 *t_cmd *tmp;
 *
 *tmp = node->cmd;
 *
 *tmp->cmd = echo
 *tmp->bin = bin.echo
 *tmp->args = echo
 *            hi
 *tmp->input_redir = a.txt = open = fd = 3 dup2(3, 0);
 *tmp->output_redir = append.txt = is_append> tmp->append = 1;
 *open("append.txt", O_RDWR | O_CREAT | O_APPEND, 0644); = 4 dup2(4, 1) fd1[1]
 */
