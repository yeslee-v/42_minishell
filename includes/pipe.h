#ifndef PIPE_H
# define PIPE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "../libs/libft/libft.h"

# define STDIN		0
# define STDOUT		1

# define BUFFER_SIZE 256 // how to set buffer size

typedef struct	s_pipe
{
	const char	*cmd[256];
	char *const	*av;
	char *const	*envp;
}				t_pipe;

typedef struct	s_parse
{
	char		*p_cmd;
	int			opt;
	char		*args;
}				t_parse;

typedef	struct	s_all
{
	int			**fd; 
	pid_t		*pid;
	t_pipe		pipe;
	t_parse		parse;
}				t_all;

/*
 * for multi-pipe
int		main(int ac, char **av, char **path);
void	print_error(char *str);
void	split_path(const char *cmd_1, char **path, t_all *all);
void	connect_in(char *file);
void	connect_out(char *file);
void	run_dup2(int std_fd, int *fd);
void	close_fd(int flag, int *fd);
void	run_execve(t_all *all);
 *
 */

int		main(int ac, char **av, char **path);

#endif
