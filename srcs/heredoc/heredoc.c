#include "../../includes/minishell.h"

extern t_conf g_sh;

void	run_hdoc(t_hdoc *hdoc, t_syntax *stx)
{
	char	*line;
	int		pid;
	int		fd[2];
	int		status;

	printf("cmd is %s\n", stx->cmd);
	char buf[100];
	pipe(fd);
	pid = fork();
	if (pid > 0)
	{
		wait(&status);
		if (!(WIFEXITED(status)))
			exit(1);
		close(fd[1]);
		while (read(fd[0], &buf, 100))
			blt_intro();
		close(fd[0]);
	}
	else if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (line)
			{
				if (!(ft_strncmp(line, hdoc->delimiter, ft_strlen(line)))) //ctrl+d
					break ;
				write(fd[1], line, ft_strlen(line));
				write(fd[1], "\n", 1);
				free(line);
			}
		}
		close(fd[1]);
		exit(0);
	}
	else
	{
		printf("fork error in second fork\n");
		exit(0);
	}
}
