#include "../includes/minishell.h"

t_conf	g_sh;

void	get_cursor_pos(int *x, int *y)
{
	int		ret;
	int		flag;
	char	ch;

	flag = 0;
	init_pos(x, y);
	set_term_cursor();
	write(0, "\033[6n", 4);
	while (1)
	{
		ret = read(0, &ch, 1);
		if (!ret)
		{
			tcsetattr(0, TCSANOW, &g_sh.term);
			return ;
		}
		else if (ch == ';')
			flag = 1;
		else if ((ch >= '0' && ch <= '9') && flag == 0)
			*x = (*x * 10) + (ch - '0');
		else if ((ch >= '0' && ch <= '9') && flag == 1)
			*y = (*y * 10) + (ch - '0');
		else if (ch == 'R')
		{
			tcsetattr(0, TCSANOW, &g_sh.term);
			break ;
		}
	}
}

void	print_test_redir_fd(void)
{
	printf("test case 1 = %s, fd = %d\n", "1234>>", get_redir_fd("1234>>"));
	printf("test case 2 = %s, fd = %d\n", "12>", get_redir_fd("12>"));
	printf("test case 3 = %s, fd = %d\n", "255<", get_redir_fd("255<"));
	printf("test case 4 = %s, fd = %d\n", "32<<", get_redir_fd("32<<"));
	printf("test case 5 = %s, fd = %d\n", "0>", get_redir_fd("0>"));
}

void	set_redirect(void)
{
	char	*line;
	char	**input_redir;
	t_process *p;
	t_redirect *o_redir;
	t_redirect *i_redir;

	line = NULL;
	input_redir = NULL;
	p = g_sh.process->head;
	while (p)
	{
		o_redir = p->o_redir->head;
		while (o_redir)
		{
			if (o_redir->type == 'O')
				o_redir->fd = open(o_redir->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (o_redir->type == 'A')
				o_redir->fd = open(o_redir->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
			o_redir = o_redir->next;
		}
		p = p->next;
	}
	p = g_sh.process->head;
	while (p)
	{
		i_redir = p->i_redir->head;
		while (i_redir)
		{
			if (i_redir->type == 'I')
			{
				i_redir->fd = open(i_redir->arg, O_RDWR);
				if (errno != 0)
					printf("braveShell : %s: %s\n", i_redir->arg, strerror(errno));
				else
				{
					while ((get_next_line(i_redir->fd, &line)) != 0)
					{
						input_redir = ft_double_strjoin(input_redir, line);
						free(line);
						line = NULL;
					}
					i_redir->buffer = input_redir;
					close(i_redir->fd);
					i_redir->fd = 0;
				}
			}	
			i_redir = i_redir->next;
		}
		p = p->next;
	}
}

void	set_heredoc(void)
{
	t_process *pipe;
	t_redirect *input;

	pipe = g_sh.process->head;
	while (pipe)
	{
		input = pipe->i_redir->head;
		while (input)
		{
			if (input->type == 'H')
				input->buffer = exec_heredoc(input->arg);
			input = input->next;
		}
		pipe = pipe->next;
	}
}

int		main(int ac, char **av, char **envp)
{
	int			ret;
	int			proc_cnt;

	/*
		*t_env		*tmp;
		*/
	if (!ac || !av)
		return (-1);
	ret = ac;
	g_sh.envp = envp;
	set_env(envp);
	set_terminal();
	while (ret)
	{
		set_signal();
		init_config();
		set_prompt();
		set_process();
		set_redirect();
		set_heredoc();
		print_system();
		proc_cnt = get_process_count();
		if (proc_cnt)
		{
			/*
				*if (proc_cnt == 1)
				*/
			/*
				*blt_intro(blt.p_cmd, blt.args);
				*/
			/*
				*else
				*    pipe_intro(proc_cnt);
				*/
		}
		free_conf(&g_sh);
	}
	system("leaks checker");
}
