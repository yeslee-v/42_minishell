#include "../../../includes/minishell.h"

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
	if (fd == -1)
	{
		g_sh.exit_status = 1;
		return (-1);
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
	g_sh.fd_backup[0] = dup(0);
	g_sh.fd_backup[1] = dup(1);
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
