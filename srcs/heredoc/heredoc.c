#include "../../includes/minishell.h"

void	hdoc_init(t_hdoc *hdoc)
{
	hdoc->delimiter = NULL;
	hdoc->arg = NULL;
}

void	run_hdoc(t_hdoc *hdoc)
{
	char	*line;
	int		pid;
	int		fd[2];
	int		status;

	char buf[100]; // by ji-kim
	pipe(fd);
	pid = fork();
	if (pid > 0) // cmd
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
		close(fd[1]);
		while (read(fd[0], &buf, 100))
			printf("%s", buf); // execve vs builtin
	}
	else if (pid == 0) // heredoc
	{
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (line)
			{
				if (!(ft_strncmp(line, hdoc->delimiter, ft_strlen(line)))) // add ctrl + d
					break ;
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				free(line);
			}
		}
	}
	else
	{
		printf("fork error in second fork\n");
		exit(0);
	}
}
