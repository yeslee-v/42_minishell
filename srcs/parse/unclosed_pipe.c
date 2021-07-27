#include "../../includes/minishell.h"

static char	*parent(int fd[2])
{
	int		status;
	char	*line;

	line = NULL;
	wait(&status);
	if (!(WIFEXITED(status)))
		exit(1);
	close(fd[1]);
	get_next_line(fd[0], &line);
	return (line);
}

static void	child(int fd[2])
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line[0] != '\0')
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
			exit(0);
		}
		if (line)
			free(line);
		rl_redisplay();
	}
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
		printf("fork error\n");
	return (line);
}
