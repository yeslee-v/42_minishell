#include "../../includes/minishell.h"

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
	ft_free_double((void **)path);
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
	t_env	*node;
	char	**tmp;

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
	int	i;

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
	char	*bin;
	char	**path;

	bin = NULL;
	path = NULL;
	if (!node || !env)
		return (NULL);
	path = split_env_value("PATH", ':', env);
	make_cmd_with_path(node, path);
	bin = find_bin(path);
	return (bin);
}
