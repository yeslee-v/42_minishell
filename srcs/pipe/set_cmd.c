#include "../../includes/minishell.h"

void	combine_cmd(const char *cmd_1, char **path, t_exec *exec)
{
	int		i;
	char	**chunk;

	i = 0;
	if (!(ft_strlen(cmd_1)))
		print_error("cmd_1 is not exists");
	chunk = ft_split(cmd_1, ' ');
	while (*path)
	{
		exec->cmd[i] = ft_strjoin(*path, chunk[0]);
		i++;
		path++;
	}
	exec->cmd[i] = NULL;
	exec->av = (char *const *)chunk;
	exec->envp = NULL;
}

void	split_path(const char *cmd_1, char **path, t_exec *exec)
{
	int		i;
	char	**str;
	char	*tmp[100];

	i = -1;
	str = NULL;
	if ((**path == 'P') && (*(*path + 1) == 'A') && (*(*path + 2) == 'T') &&
		(*(*path + 3) == 'H'))
	{
		str = ft_split(*path, ':');
		while (str[++i])
		{
			tmp[i] = ft_strjoin(str[i], "/");
			free(str[i]);
		}
		tmp[i] = NULL;
		free(str);
		combine_cmd(cmd_1, tmp, exec);
	}
}
