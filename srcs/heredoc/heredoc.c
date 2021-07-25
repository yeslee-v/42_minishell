#include "../../includes/minishell.h"

extern t_conf	g_sh;

char			**exec_heredoc(char *delimiter)
{
	pid_t pid;
	char *line;
	char *ret;
	char **str;
	int	fd[2];
	int eof;
	int status;

	str = NULL;
	eof = -1;
	pipe(fd);
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
		close(fd[1]);
		while (eof != 0)
		{
			eof = get_next_line(fd[0], &ret);
			if (eof == -1)
				printf("gnl error\n");
			str = ft_double_strjoin(str, ret);
			free(ret);
			ret = NULL;
		}
		if (eof == 0)
			return (str);
	}
	else if (pid == 0)
	{
		while (1)
		{
			line = readline("> ");
			if ((ft_strcmp(line, delimiter)) == 0)
			{
				close(fd[1]);
				exit(0);
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			if (line)
				free(line);
		}
	}
	else
	{
		printf("fork error in second fork\n");
		exit(0);
	}
	return (NULL);
}
