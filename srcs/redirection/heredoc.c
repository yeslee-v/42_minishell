#include "../../includes/minishell.h"

extern t_conf	g_sh;

void	write_text(int fd[2], int hdoc_fd)
{
	char	*ret;
	int		eof;
	int		status;

	eof = -1;
	ret = NULL;
	wait(&status);
	if (!(WIFEXITED(status)))
		exit(1);
	close(fd[1]);
	while (eof != 0)
	{
		eof = get_next_line(fd[0], &ret);
		if (eof == -1)
			printf("gnl error\n");
		ret = ft_strjoin(ret, "\n");
		if (eof != 0)
			write(hdoc_fd, ret, ft_strlen(ret));
		free(ret);
		ret = NULL;
	}
	close(fd[0]);
	if (ret)
		free(ret);
}

void	receive_text(int fd[2], char *delimeter)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if ((ft_strcmp(line, delimeter)) == 0)
		{
			close(fd[0]);
			close(fd[1]);
			exit(0);
		}
		if (line != NULL)
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		if (line)
			free(line);
	}
}

void	exec_heredoc(char *delimeter, int hdoc_fd)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid > 0)
		write_text(fd, hdoc_fd);
	else if (pid == 0)
		receive_text(fd, delimeter);
	else
	{
		printf("fork error in second fork\n");
		exit(0);
	}
}
