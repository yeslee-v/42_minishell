#include "../includes/minishell.h"

t_conf	g_sh;

int		main(int ac, char **av, char **envp)
{
	int	ret;
	int	proc_cnt;

	if (!ac || !av)
		return (-1);
	g_sh.envp = envp;
	set_env(envp);
	set_terminal();
	while (1)
	{
		set_signal();
		init_config();
		set_prompt();
		set_process();
		ret = set_redirect();
		print_system();
		proc_cnt = get_process_count();
		if (proc_cnt)
			intro(proc_cnt);
		free_conf(&g_sh);
	}
}

/*
 *ret == 1 인 경우 heredoc에서 인터럽트 발생 -> 바로 메모리 해제하고 
 *다시 프롬포트 함수로이동-> g_sh.exit_status = 1
 *ret != 1 인경우 정상 실행 빌트인 or EXEC program
 */
