#include "../../../includes/minishell.h"

extern t_conf	g_sh;

int	set_output_redir_node(t_redirect *out)
{
	if (out->type == 'O')
		out->fd = open(out->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (out->type == 'A')
		out->fd = open(out->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (out->fd == -1)
		return (redir_error(out->arg, strerror(errno)));
	else
		close_redir_fd(out);
	return (0);
}

int	set_input_redir_node(t_redirect *input)
{
	input->fd = open(input->arg, O_RDWR);
	if (input->fd == -1)
		return (redir_error(input->arg, strerror(errno)));
	if (input->fd > 0)
		close_redir_fd(input);
	return (0);
}

int	set_heredoc(t_process *pipe)
{
	char		*file;
	int			ret;
	t_redirect	*node;

	while (pipe)
	{
		file = make_hdoc_file_name(pipe->i);
		node = pipe->con->redir->head;
		while (node)
		{
			if (node->type == 'H')
			{
				node->fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
				ret = exec_heredoc(node->arg, node->fd);
				if (node->fd > 0)
					close_redir_fd(node);
				if (ret == 1)
					return (exit_hdoc(&file, ret));
			}
			node = node->next;
		}
		free(file);
		pipe = pipe->next;
	}
	return (0);
}

int	set_all_redir_lst(t_process *pipe)
{
	int			ret;
	t_control	*con;
	t_redirect	*node;

	ret = 0;
	con = pipe->con;
	node = con->redir->head;
	while (node && ret != 1)
	{
		if (ft_strchr("AO", node->type))
			ret = set_output_redir_node(node);
		else if (node->type == 'I')
			ret = set_input_redir_node(node);
		node = node->next;
		if (ret == 1)
			pipe->redir_err = 1;
	}
	return (ret);
}

int	set_redirect(t_lst *process)
{
	int			ret;
	t_process	*pipe;

	pipe = NULL;
	if (!process->head)
		return (-1);
	pipe = process->head;
	ret = set_heredoc(pipe);
	g_sh.exit_status = ret;
	if (ret == 1)
		return (1);
	return (ret);
}
