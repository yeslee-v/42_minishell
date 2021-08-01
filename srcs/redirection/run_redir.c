#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	dup_close(int fd, int fd_std)
{
	dup2(fd, fd_std);
	close(fd);
}

int	in_redir(t_cmd *proc)
{
	int	fd;

	fd = open(proc->input_redir, O_RDONLY);
		printf("fd is %d\n", fd);
	if (fd == -1)
	{
		if (proc->cmd)
			free(proc->cmd);
		proc->cmd = ft_strdup(proc->input_redir);
		if (proc->arg)
			free(proc->arg);
		proc->arg = NULL;
		return (fd);
	}
	dup_close(fd, READ);
	return (0);
}

void	out_redir(t_cmd *proc)
{
	int	fd;

	fd = open(proc->output_redir, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup_close(fd, WRITE);
}

void	append_redir(t_cmd *proc)
{
	int	fd;

	fd = open(proc->output_redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup_close(fd, WRITE);
}

int	redir_init(t_cmd *proc)
{
	if (proc->input_redir)
	{
		if (in_redir(proc) == -1)
			return (1);
	}
	if (proc->output_redir)
	{
		if (!(proc->append))
			out_redir(proc);
		else if (proc->append)
			append_redir(proc);
	}
	return (0);
}
