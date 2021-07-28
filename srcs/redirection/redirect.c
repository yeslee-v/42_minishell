#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	set_output_redirect(void)
{
	t_process	*pipe;
	t_redirect	*out;

	pipe = g_sh.process->head;
	while (pipe)
	{
		out = pipe->o_redir->head;
		while (out)
		{
			if (out->type == 'O')
				out->fd = open(out->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (out->type == 'A')
				out->fd = open(out->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (errno != 0)
				printf("BraveShell : %s: %s\n", out->arg, strerror(errno));
			if (out != pipe->o_redir->tail)
			{
				close(out->fd);
				out->fd = 0;
			}
			out = out->next;
		}
		pipe = pipe->next;
	}
}

void	set_input_redirect(void)
{
	t_process	*pipe;
	t_redirect	*input;

	pipe = g_sh.process->head;
	while (pipe)
	{
		input = pipe->i_redir->head;
		while (input)
		{
			if (input->type == 'I')
			{
				input->fd = open(input->arg, O_RDWR);
				if (errno != 0)
					printf("braveShell : %s: %s\n", input->arg, strerror(errno));
				if (input->fd > 0)
				{
					close(input->fd);
					input->fd = 0;
				}
			}	
			input = input->next;
		}
		pipe = pipe->next;
	}
}

void	close_input_fd(t_redirect *input)
{
	close(input->fd);
	input->fd = 0;
}

int	set_heredoc(void)
{
	int			ret;
	t_process	*pipe;
	t_redirect	*input;

	pipe = g_sh.process->head;
	while (pipe)
	{
		input = pipe->i_redir->head;
		while (input)
		{
			if (input->type == 'H')
			{
				input->fd = open(".hdoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
				ret = exec_heredoc(input->arg, input->fd);
				if (input->fd > 0)
					close_input_fd(input);
				if (ret == 1)
					return (ret);
			}
			input = input->next;
		}
		pipe = pipe->next;
	}
	return (0);
}

int	set_redirect(void)
{
	int	ret;

	ret = 0;
	set_output_redirect();
	set_input_redirect();
	ret = set_heredoc();
	return (ret);
}
