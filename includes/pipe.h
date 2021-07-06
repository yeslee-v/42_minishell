#ifndef PIPE_H
# define PIPE_H

# include "../libs/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define STDIN 0
# define STDOUT 1

# define BUFFER_SIZE 256

/*
 *for pipex
 */
typedef struct		s_pipe
{
	const char		*cmd[256];
	char *const *av;
	char *const *envp;
}					t_pipe;

/*
 *builtin function echo
 */
typedef struct		s_parse
{
	char			*p_cmd;
	int				opt;
	int				u_flag;
	char			*args;
}					t_parse;

/*
 * builtin function export, unset 
 */
typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

/*
 *total functions
 */
typedef struct		s_all
{
	int				**fd;
	pid_t			*pid;
	t_env			env;
	t_pipe			pipe;
	t_parse			parse;
}					t_all;

/*
 * multi-pipe
int					main(int ac, char **av, char **path);
void				print_error(char *str);
void				split_path(const char *cmd_1, char **path, t_all *all);
void				connect_in(char *file);
void				connect_out(char *file);
void				run_dup2(int std_fd, int *fd);
void				close_fd(int flag, int *fd);
void				run_execve(t_all *all);
 *
 */

/*
 * builtin functions
 * int					main(int ac, char **av, char **path);
 */

/*
 * heredoc
 */
int					main(int ac, char **av);

#endif
