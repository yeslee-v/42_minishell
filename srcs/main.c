#include "../includes/minishell.h"

t_conf	g_sh;

void	open_path(char **path)
{
	int i;
	int fd;

	i = -1;
	fd = 0;
	while (path[++i])
	{
		fd = open(path[i], O_RDONLY);
		printf("fd = %d\n", fd);
		if (fd != -1)
			printf("%s\n", path[i]);
	}

}

void	cmd_with_path(t_process *node, char **path)
{
	int i;
	t_cmd *tmp;

	i = -1;
	tmp = node->cmd;
	while (path[++i])
		path[i] = ft_strcjoin(path[i], tmp->cmd, '/');
	print_double_str(path);
}

char	**split_env_value(char *key, char c, t_lst *env)
{
	t_env *node;
	char **tmp;

	if (!key || !env || c < 0)
		return (NULL);
	tmp = NULL;
	node = search_env_node(key, env);
	tmp = ft_split(node->value, c);
	return (tmp);
}

int		main(int ac, char **av, char **envp)
{
	int	ret;
	int	proc_cnt;
	char	**path;

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
		path = split_env_value("PATH", ':', g_sh.env);
		cmd_with_path(g_sh.process->head, path);
		open_path(path);
		print_system();
		proc_cnt = get_process_count();
		/*
		 *if (proc_cnt)
		 *    intro(proc_cnt);
		 */
		free_conf(&g_sh);
	}
}

/*
 *ret == 1 인 경우 heredoc에서 인터럽트 발생 -> 바로 메모리 해제하고 
 *다시 프롬포트 함수로이동-> g_sh.exit_status = 1
 *ret != 1 인경우 정상 실행 빌트인 or EXEC program
 */


t_prcoess *node;
t_cmd *tmp;

tmp = node->cmd;

tmp->cmd = echo
tmp->bin = bin.echo
tmp->args = echo
			hi
tmp->input_redir = a.txt = open = fd = 3 dup2(3, 0);
tmp->output_redir = append.txt = is_append> tmp->append = 1; open("append.txt", O_RDWR | O_CREAT | O_APPEND, 0644); = 4 dup2(4, 1)
