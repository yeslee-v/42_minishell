#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			combine_cmd(t_cmd *proc, char **path)
{
	int			i;
	
	i = 0;
	if (!(ft_strlen(proc->cmd)))
		print_error("cmd is not exists");
	while (*path)
	{
		g_sh.exec.cmd[i] = ft_strjoin(*path, proc->cmd);
		i++;
		path++;
	}
	g_sh.exec.cmd[i] = NULL;
	g_sh.exec.av = (char *const *)proc->args;
	g_sh.exec.envp  NULL;
	/*
		*proc_lst = proc_lst->next;
		*/
}

void			split_path(t_cmd *proc, char *path)
{
	int		i;
	char	**str;
	char	*tmp[100];

	i = -1;
	str = NULL;
	str = ft_split(path, ':');
	while (str[++i])
		tmp[i] = ft_strjoin(str[i], "/");
	tmp[i] = NULL;
	free(str);
	combine_cmd(proc, tmp);
}
