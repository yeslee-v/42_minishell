#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			combine_cmd(char *cmd, char **path)
{
	int			i;
	t_process	*proc_lst;
	t_cmd		*proc;

	proc_lst = g_sh.process->head;
	proc = proc_lst->cmd;
	printf("args is %s\n", proc->args[0]);
	i = 0;
	if (!(ft_strlen(cmd)))
		print_error("cmd is not exists");
	while (*path)
	{
		g_sh.exec.cmd[i] = ft_strjoin(*path, cmd);
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

void			split_path(char *cmd, char *path)
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
	combine_cmd(cmd, tmp);
}
