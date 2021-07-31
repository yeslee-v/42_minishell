#include "../../includes/minishell.h"

void	in_redir(t_cmd *proc)
{
	int	fd;

	fd = open(proc->input_redir, O_RDONLY);
	dup_close(fd, READ);
}

void	out_redir(t_cmd *proc)
{
	int	fd;

	fd = open(proc->output_redir, O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("fd is %d\n", fd);
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
		in_redir(proc);
	if (proc->output_redir)
	{
		if (!(proc->append))
			out_redir(proc);
		else if (proc->append)
			append_redir(proc);
	}
	return (0);
}
