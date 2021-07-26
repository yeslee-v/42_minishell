#include "../../includes/minishell.h"

extern t_conf	g_sh;

/*
 *int		single_pipe(char **av, char *path)
 *{
 *    pid_t	pid;
 *    t_exec	exec;
 *    int		status;
 *
 *    printf("path is %s\n", *path);
 *    pid = fork();
 *    if (pid > 0)
 *    {
 *        wait(&status);
 *        if (!(WIFEXITED(status)))
 *            exit(1);
 *    }
 *    else if (pid == 0)
 *        child_proc(av, path, &exec);
 *    else
 *        print_error("fork error");
 *    return (0);
 *}
 */

int				multi_pipe(int cnt, char *path)
{
	t_all	all;
	int		mid_cmd_cnt;

	cnt = get_process_count();
	mid_cmd_cnt = cnt - 3;
	printf("mid is %d\n", mid_cmd_cnt);
	if (!(all.pid = malloc(sizeof(pid_t) * cnt)))
		return (0);
	path = NULL;
	/*
		*all.pid[0] = fork();
		*if (all.pid[0] > 0) // grand
		*    set_wait();
		*else if (all.pid[0] == 0) // parents or child
		*{
		*    middle_proc(cnt, av, path, &all);
		*    run_dup2(0, all.fd[mid_cmd_cnt - 1]);
		*    split_path(av[cnt - 1], path, &all.exec);
		*    connect_out(av[cnt]);
		*    run_execve(&all.exec);
		*}
		*else
		*    print_error("fork error");
		*/
	return (0);
}

void			pipe_intro(int proc_cnt)
{
	char	*path;
	t_lst	*envl;

	envl = g_sh.env;
	path = search_env_value("PATH", envl);
	printf("proc_cnt is %d\n", proc_cnt);
	/*
		*if (proc_cnt == 2)
		*    single_pipe(path);
		*else if (proc_cnt > 2)
		*/
	multi_pipe(proc_cnt, path);
}
