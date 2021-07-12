#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libs/includes/libft.h"
#include <curses.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <term.h>
#include <termcap.h>
#include <termios.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define QUOTE 81
#define D_QUOTE 68

#define BUF_SIZE 1

#define PIPE "|"
#define O_REDIR ">"
#define I_REDIR "<"
#define A_REDIR ">>"
#define HEREDOC "<<"

#define PROMPT "\033[1;32mBraveShell\033[0;31m$\033[0m "
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\03[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"

typedef struct			s_lst
{
	void					*head;
	void					*tail;
}						t_lst;

typedef struct			s_lexer
{
	char					*lex;
	int					s_quote;
	int					e_quote;
	int					is_quote;
	int					err;
}						t_lexer;

typedef struct			s_token
{
	char					*token;
	char					type;
	int					i;
	int					st;
	int					ed;
	struct s_token			*next;
	struct s_token			*prev;
}						t_token;

typedef struct			s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
	struct s_env			*prev;
}						t_env;

typedef struct			s_redir
{
	char					type;
	char					*target;
	char					*arg;
}						t_redir;

typedef struct			s_hdoc
{
	char					*delimiter;
	char					*arg;
}						t_hdoc;

typedef struct			s_syntax
{
	char					*cmd;
	char					*arg_line;
	char					**arg_word;
	struct s_syntax		*next;
	struct s_syntax		*prev;
}						t_syntax;

typedef struct			s_process
{
	t_lst					*syntax;
	struct s_process		*next;
	struct s_process		*prev;
}						t_process;

typedef struct			s_tool
{
	int					i;
	int					is_quote;
	int					st;
	int					ed;
	t_lst					*token;
}						t_tool;

typedef struct			s_parse
{
	int					start;
	int					pipe;
	char					*cmd;
	char					*arg;
	t_lst					*syntax;
}						t_parse;

typedef struct			s_conf
{
	char					*cmd;
	char					**envp;
	t_lst					*env;
	t_lexer				*lexer;
	t_lst					*token;
	t_lst					*process;
	struct termios			term;
}						t_conf;

typedef struct			s_pipe
{
	const char				*cmd[256];
	char *const *av;
	char *const *envp;

	int					fd[2];
}						t_pipe;

typedef struct			s_blt
{
	char					*p_cmd;
	int					opt;
	int					up_flag;
	char					*args;
}						t_blt;

typedef struct			s_all
{
	int					**fd;
	pid_t					*pid;
	t_env					env;
	t_pipe					pipe;
	t_hdoc					hdoc;
	t_blt					blt;
}						t_all;

/*
 * - lexer
 *analyze_space
 *analyze_quote
 *analyze_operator
 */
void					lexer(char *cmd);
/*
 *token
 */
void					tokenizer(t_conf *conf, char *lex);

void					print_error(char *msg);
void					make_token(t_lst *lst, int st, int ed);
void					make_env(t_lst *lst, char *key, char *value);
char					*ft_strrdup(char *s, int st, int ed);
int						ft_isspace(int c);
int						ft_isquote(char c);
void					init_lst(t_lst *lst);
void					init_lexer(t_lexer *lexer);
void					free_lexer(t_lexer *lexer);
int						ft_isspec(char *cmd, int i);
void					init_tool(t_tool *tool);
char					*ft_strjoin_sp(char *s1, char *s2);

/*
 * multi-pipe
 */
int						intro_pipe(int ac, char **av, char **path);
void					print_error(char *str);
void					split_path(const char *cmd_1, char **path, t_all *all);
void					connect_in(char *file);
void					connect_out(char *file);
void					run_dup2(int std_fd, int *fd);
void					close_fd(int flag, int *fd);
void					run_execve(t_all *all);

/*
 * builtin functions
 */
int						intro_blt(int ac, char **av, char **path);
void					run_echo(char **av, t_all *all);
void					run_cd(char **av, char **path, t_all *all);
void					run_env(char **path);
void					run_exit(t_all *all);
void					run_export(char **av, char **path, t_all *all);
void					run_pwd();
void					run_unset(int ac, char **av, char **path, t_all *all);

/*
 * heredoc
 */
/*
 *int					main(int ac, char **av, char **path);
 */

#endif
