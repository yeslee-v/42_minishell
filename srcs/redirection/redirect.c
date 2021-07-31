#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	close_redir_fd(t_redirect *redir)
{
	close(redir->fd);
	redir->fd = 0;
}

int	print_redir_error(char *file, char *err_msg)
{
	ft_putstr_fd("BraveShell : ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	set_output_redir_node(t_redirect *out)
{
	if (out->type == 'O')
		out->fd = open(out->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (out->type == 'A')
		out->fd = open(out->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (out->fd == -1)
		return (print_redir_error(out->arg, strerror(errno)));
	else
		close_redir_fd(out);
	return (0);
}

int	set_input_redir_node(t_redirect *input)
{
	input->fd = open(input->arg, O_RDWR);
	if (input->fd == -1)
		return (print_redir_error(input->arg, strerror(errno)));
	if (input->fd > 0)
		close_redir_fd(input);
	return (0);
}

char *make_hdoc_file_name(int i)
{
	char *hdoc;
	char *num;

	hdoc = ft_strdup(".hdoc");
	num = ft_itoa(i);
	hdoc = ft_strcjoin(hdoc, num, '_');
	if (num)
		free(num);
	return (hdoc);
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
				{
					free(file);
					return (ret);
				}
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
	int ret;
	t_control *con;
	t_redirect *node;

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
	}
	pipe->redir_err = 1;
	return (ret);
}

void	init_status(t_status *node)
{
	node->hdoc = 0;
	node->input = 0;
	node->output = 0;
	node->result = 0;
}

int	set_redirect(t_lst *process)
{
	t_status ret;
	t_process *pipe;

	pipe = NULL;
	init_status(&ret);
	if (!process->head)
		return (-1);
	pipe = process->head;
	ret.hdoc = set_heredoc(pipe);
	g_sh.exit_status = ret.hdoc;
	if (ret.hdoc == 1)
		return (1);
	pipe = process->head;
	/*while (pipe)*/
	/*{*/
		/*ret.result = set_all_redir_lst(pipe);*/
		/*g_sh.exit_status = ret.result;*/
		/*pipe = pipe->next;*/
	/*}*/
	/*if (ret.result == 1)*/
		/*return (1);*/
	return (ret.result);
}
