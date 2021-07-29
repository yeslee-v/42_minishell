#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	hdoc_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		exit(1);
	}
}

int	write_text(int fd[2], int hdoc_fd)
{
	char	*ret;
	int		eof;
	int		status;

	eof = -1;
	signal(SIGINT, SIG_IGN);
	close(fd[WRITE]);
	wait(&status);
	if (!(WIFEXITED(status)))
		exit(1);
	if (status == 256)
		return (1);
	while (eof != 0)
	{
		eof = get_next_line(fd[READ], &ret);
		if (eof == -1)
			return (-1);
		ret = ft_strjoin(ret, "\n");
		if (eof > 0)
			write(hdoc_fd, ret, ft_strlen(ret));
		free(ret);
		ret = NULL;
	}
	close(fd[READ]);
	return (0);
}

void	receive_text(int fd[2], char *delimeter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		signal(SIGINT, hdoc_sig_handler);
		line = readline("> ");
		if (!line || ((ft_strcmp(line, delimeter)) == 0))
		{
			if (!line)
				move_cursor(NULL, 1, 2);
			close(fd[READ]);
			close(fd[WRITE]);
			exit(0);
		}
		if (line != NULL)
		{
			write(fd[WRITE], line, ft_strlen(line));
			write(fd[WRITE], "\n", 1);
		}
		if (line)
			free(line);
	}
}

int	exec_heredoc(char *delimeter, int hdoc_fd)
{
	int		ret;
	pid_t	pid;
	int		fd[2];

	ret = 0;
	pipe(fd);
	pid = fork();
	if (pid > 0)
		ret = write_text(fd, hdoc_fd);
	else if (pid == 0)
		receive_text(fd, delimeter);
	else
	{
		printf("fork error in second fork\n");
		exit(0);
	}
	g_sh.exit_status = ret;
	return (ret);
}