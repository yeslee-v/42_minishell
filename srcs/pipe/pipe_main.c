#include "../../includes/minishell.h"

extern t_conf g_sh;

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
 *
 *int		multi_pipe(char **av, char *path)
 *{
 *    int		args_cnt;
 *    t_all	all;
 *
 *    int mid_cmd_cnt; // cmds using while
 *    args_cnt = ac - 1;
 *    mid_cmd_cnt = args_cnt - 3;
 *    if (!(all.pid = malloc(sizeof(pid_t) * args_cnt)))
 *        return (0);
 *    all.pid[0] = fork();
 *    if (all.pid[0] > 0) // grand
 *        set_wait();
 *    else if (all.pid[0] == 0) // parents or child
 *    {
 *        middle_proc(args_cnt, av, path, &all);
 *        run_dup2(0, all.fd[mid_cmd_cnt - 1]);
 *        split_path(av[args_cnt - 1], path, &all.exec);
 *        connect_out(av[args_cnt]);
 *        run_execve(&all.exec);
 *    }
 *    else
 *        print_error("fork error");
 *    return (0);
 *}
 */

void	pipe_intro(int proc_cnt)
{
	char *path;
	t_lst *envl;

	envl = g_sh.env;
	path = search_env_value("PATH", envl);
	proc_cnt = 0;
	/*
	 *if (proc_cnt == 2)
	 *    single_pipe(char **av, path);
	 *else if (proc_cnt > 2)
	 *    multi_pipe(char **av, path);
	 */
}
