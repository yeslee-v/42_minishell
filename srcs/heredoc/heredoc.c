#include "../../includes/minishell.h"

extern t_conf	g_sh;

void			hdoc_parents(int fd[2], t_syntax *stx)
{
	int		status;
	char	buf[100];

	wait(&status);
	if (!(WIFEXITED(status)))
		exit(1);
	close(fd[1]);
	if (!(stx->next)) // << delimeter
	{
		while (read(fd[0], &buf, 100))
		{
			printf("%s\n", buf);
			/*printf("heredoc's cmd is %s\n", stx->cmd);*/
		}
	}
	else // cmd << delimeter
	{
		// return 
		dup2(fd[0], 1);
		//not_blt(fd[0], stx->cmd, )
		blt_intro(stx->cmd, buf); // buf => stx->cmd

	}
	close(fd[0]);
	exit(0);
}

void			hdoc_child(int fd[2], t_hdoc *hdoc)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (!(ft_strcmp(line, hdoc->delimiter))) // ctrl+d
				break ;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
	}
	close(fd[1]);
	exit(0);
}

void			run_hdoc(t_hdoc *hdoc, t_syntax *stx)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid > 0)
	{
		printf("0 -> %d\n", getpid());
		hdoc_parents(fd, stx);
		printf("3\n");
	}
	else if (pid == 0)
	{
		printf("1 -> %d\n", getpid());
		hdoc_child(fd, hdoc);
		printf("2\n");
	}
	else
	{
		printf("fork error in second fork\n");
		exit(0);
	}
}
