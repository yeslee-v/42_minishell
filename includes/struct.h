#ifndef STRUCT_H
# define STRUCT_H

#include <unistd.h>
#include <termios.h>

typedef struct			s_lst
{
	void				*head;
	void				*tail;
}						t_lst;

typedef struct			s_lexer
{
	char				*lex;
	int					s_quote;
	int					e_quote;
	int					is_quote;
	int					err;
}						t_lexer;

typedef struct			s_token
{
	char				*token;
	char				type;
	int					syntax;
	int					i;
	int					st;
	int					ed;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct			s_redirect
{
	char				type;
	char				*arg;
	int					fd;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}						t_redirect;

typedef struct			s_cmd
{
	char				*cmd;
	char				*arg;
	char				**args;
}						t_cmd;

typedef struct			s_process
{
	t_cmd				*cmd;
	t_lst				*i_redir;
	t_lst				*o_redir;
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct			s_tool
{
	int					i;
	int					is_quote;
	int					st;
	int					ed;
	int					pipe;
	int					redir;
	int					a_redir;
	int					heredoc;
}						t_tool;

typedef struct			s_conf
{
	char				*cmd;
	char				**envp;
	int					exit_status;
	t_lst				*env;
	t_lexer				*lexer;
	t_lst				*token;
	t_lst				*process;
	struct termios		term;
}						t_conf;

typedef struct			s_exec
{
	const char			*cmd[256];
	char *const *av;
	char *const *envp;
	int					fd[2];
}						t_exec;

typedef struct			s_blt
{
	char				*p_cmd;
	int					opt;
	int					up_flag;
	char				*args;
}						t_blt;

typedef struct			s_all
{
	int **fd; /// multi_pipe
	pid_t				*pid;
	t_env				env;
	t_exec				exec;
}						t_all;

#endif
