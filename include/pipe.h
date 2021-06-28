#ifndef PIPE_H
# define PIPE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libs/libft/libft.h"

typedef struct	s_pipe
{
	char	*cmd;
	char 	fd[2];
	int		p_flag;
}				t_pipe;

typedef	struct	s_all
{
	pid_t		*pid;
	t_pipe		pipe;
}				t_all;

/*typedef struct	s_all
{
	t_pipe		pipe;
	t_pid		pid;
}*/				t_all;

int	main(int ac, char **av);

#endif
