#include "../includes/minishell.h"

t_conf	g_sh;

char	*find_bin(char **path)
{
	int		i;
	int		fd;
	char	*ret;

	i = -1;
	fd = 0;
	if (!path)
		return (NULL);
	while (path[++i])
	{
		fd = open(path[i], O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			ret = ft_strdup(path[i]);
			if (path)
				ft_free_double((void **)path);
			path = NULL;
			return (ret);
		}
	}
	return (NULL);
}

void	make_cmd_with_path(t_cmd *node, char **path)
{
	int i;

	if (!node || !path)
		return ;
	i = -1;
	if (!node || !node->cmd)
		return ;
	while (path[++i])
		path[i] = ft_strcjoin(path[i], node->cmd, '/');
}

char	**split_env_value(char *key, char c, t_lst *env)
{
	t_env *node;
	char **tmp;

	if (!key || !env || c < 0)
		return (NULL);
	tmp = NULL;
	node = search_env_node(key, env);
	if (!node)
		return (NULL);
	tmp = ft_split(node->value, c);
	return (tmp);
}

int	check_cmd_contain_path(t_cmd *node)
{
	int i;

	i = -1;
	if (!node)
		return (-1);
	if (node->cmd == NULL)
		return (-1);
	if ((ft_strncmp(node->cmd, "./", 2)) == 0)
		return (1);
	else if ((ft_strncmp(node->cmd, "../", 3)) == 0)
		return (2);
	else if ((ft_strncmp(node->cmd, "~/", 2)) == 0)
		return (3);
	else if ((ft_strncmp(node->cmd, "/", 1)) == 0)
		return (4);
	else
	{
		while (node->cmd[++i])
			if( node->cmd[i] == '/')
				return (5);
	}
	return (0);
}

char	*make_bin_with_path(t_cmd *node, t_lst *env)
{
	char *bin;
	char **path;

	bin = NULL;
	path = NULL;
	if (!node || !env)
		return (NULL);
	path = split_env_value("PATH", ':', env);
	make_cmd_with_path(node, path);
	bin = find_bin(path);
	return (bin);
}

void	get_redirect_file(t_lst *redir, t_cmd *tmp)
{
	t_redirect *node;

	if (!redir)
		return ;
	node = redir->tail;
	if (node && node->arg)
	{
		if (ft_strchr("IH", node->type))
			tmp->input_redir = ft_strdup(node->arg);
		else if (ft_strchr("OA", node->type))
		{
			tmp->output_redir = ft_strdup(node->arg);
			if (node->type == 'A')
				tmp->append = 1;
		}
	}
}

void	parse_cmd(t_process *node, t_lst *env)
{
	t_cmd	*tmp;
	int		ret;

	if (!node || !env)
		return ;
	tmp = node->cmd;
	ret = check_cmd_contain_path(tmp);
	if (ret == -1)
		return ;
	else if (ret > 0)
		tmp->bin = ft_strdup(tmp->cmd);
	else
		tmp->bin = make_bin_with_path(tmp, env);
	get_redirect_file(node->o_redir, tmp);
	get_redirect_file(node->i_redir, tmp);
	getcwd(tmp->dir, 2048);
}

void	analyze_cmd(void)
{
	t_process *node;

	node = NULL;
	if (!g_sh.process)
		return ;
	node = g_sh.process->head;
	while (node)
	{
		parse_cmd(node, g_sh.env);
		node = node->next;
	}
}

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
		if (ret != 1)
		{
			analyze_cmd();
			proc_cnt = get_process_count();
			if (proc_cnt)
				intro(proc_cnt);
		}
		print_system();
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
 *tmp->output_redir = append.txt = is_append> tmp->append = 1; open("append.txt", O_RDWR | O_CREAT | O_APPEND, 0644); = 4 dup2(4, 1)
 *fd1[1]
 */
