#include "../../includes/minishell.h"

static void	unclosed_pipe_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		exit(1);
	}
}

static char	*parent(int fd[2])
{
	int		eof;
	int		status;
	char	*line;

	line = NULL;
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (!(WIFEXITED(status)))
		exit(1);
	if (status == 256)
		return (NULL);
	eof = get_next_line(fd[0], &line);
	close(fd[0]);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static void	child(int fd[2])
{
	char	*line;

	line = NULL;
	close(fd[0]);
	while (1)
	{
		signal(SIGINT, unclosed_pipe_sig_handler);
		line = readline("> ");
		if (!line)
		{
			close(fd[1]);
			move_cursor(ERR_TOKEN_EOF, 1, 2);
			exit(0);
		}
		else if (line[0] != '\0')
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
			close(fd[1]);
			exit(0);
		}
	}
	if (line)
		free(line);
}

char	*unclosed_pipe(void)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	pipe(fd);
	line = NULL;
	pid = fork();
	if (pid > 0)
		line = parent(fd);
	else if (pid == 0)
		child(fd);
	else
		ft_putstr_fd("Fork error\n", 2);
	return (line);
}
