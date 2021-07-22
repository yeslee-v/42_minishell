#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/includes/libft.h"
# include <curses.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define QUOTE 81
# define D_QUOTE 68

# define BUF_SIZE 1

# define PIPE "|"
# define O_REDIR ">"
# define I_REDIR "<"
# define A_REDIR ">>"
# define HEREDOC "<<"

# define PROMPT "\033[1;32mBraveShell\033[0;31m$\033[0m "
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\03[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

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
	int					i;
	int					st;
	int					ed;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct			s_args
{
	char				*arg;
	int					opt;
	struct s_args		*next;
	struct s_args		*prev;
}						t_args;

typedef struct			s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct			s_redir
{
	char				type;
	char				*target;
	char				*arg;
}						t_redir;

typedef struct			s_hdoc
{
	char				*delimiter;
	char				*arg;
}						t_hdoc;

typedef struct			s_syntax
{
	char				*cmd;
	char				*arg_line;
	char				**arg_word;
	struct s_syntax		*next;
	struct s_syntax		*prev;
}						t_syntax;

typedef struct			s_process
{
	t_lst				*syntax;
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct			s_tool
{
	int					i;
	int					is_quote;
	int					st;
	int					ed;
}						t_tool;

typedef struct			s_conf
{
	char				*cmd;
	char				**envp;
	int					end_pipe;
	int					exit_status;
	t_lst				*env;
	t_lexer				*lexer;
	t_lst				*token;
	t_lst				*process;
	struct termios		term;
}						t_conf;

/*
 *for execve & pipe
 */
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
	int					**fd; /// multi_pipe
	pid_t				*pid;
	t_env				env;
	t_exec				exec;
}						t_all;

/*
 * - lexer
 *	analyze_space
 *	analyze_quote
 *	analyze_operator
 */
t_lexer					*lexer(char *cmd);

/*
 * - token
 *   analyze_type
 *   set_index
 */
void					tokenizer(char *lex);

/*
 * - parser
 *   parse syntax
 *   parse redir
 *   parse process
 */
t_token					*parser(t_lst *process, t_token *tok);

/*
 *make_struct
 */
void					save_process(t_lst *lst, t_lst *syntax);
void					make_syntax(t_lst *lst, char *cmd, char *arg);
void					make_token(t_lst *lst, int st, int ed);
void					make_env(t_lst *lst, char *key, char *value);

/*
 *cursor
 */
void					get_cursor_pos(int *x, int *y);
char					**split_arg(char *arg);
/*
 *init
 */
void					init_lst(t_lst *lst);
void					init_lexer(t_lexer *lexer);
void					init_tool(t_tool *tool);
void					init_config(void);
void					init_pos(int *x, int *y);

/*
 *utils
 */
char					*ft_strrdup(char *s, int st, int ed);
int						ft_isspace(int c);
int						ft_isquote(char c);
int						ft_isspec(char *cmd, int i);
char					*ft_strjoin_sp(char *s1, char *s2);
char					**ft_split_env(char *env);

/*
 *free
 */
void					free_conf(t_conf *conf);
void					free_env(t_lst *env);
void					free_syntax(t_lst *syntax);
void					free_process(t_lst *process);
void					free_lexer(t_lexer *lexer);
void					free_token(t_lst *token);
void					free_env_node(t_env *env);
/*
 *print_utils
 */
void					print_syntax(t_lst *syntax);
void					print_process(t_lst *process);
void					print_env(t_lst *env);
void					print_error(char *msg);
void					print_token(t_lst *token);
void					print_system(void);

/*
 *set
 */
void					set_env(char **envp);
void					set_terminal(void);
void					set_signal(void);
void					set_prompt(void);
void					set_process(void);
void					set_term_cursor(void);
/*
 *exit
 */
void					exit_shell(int num);

/*
 *utils
 */
int						get_redir_fd(char *cmd);
void					delete_env_node(char *key, t_lst *env);
int						get_process_count(void);

/*
 *single-pipe
 */
int						s_pipe_intro(int ac, char **av, char **path);
void					print_error(char *str);
void					child_proc(char **av, char **path, t_exec *exec);
void					parents_proc(char **av, char **path, t_exec *exec);
void					split_path(const char *cmd_1, char **path, t_exec *exec);
void					combine_cmd(const char *cmd_1, char **path, t_exec *exec);
void					connect_in(char *file);
void					connect_out(char *file);
void					run_dup2(int std_fd, int *fd);
void					close_fd(int flag, int *fd);
void					run_execve(t_exec *exec);

/*
 * multi-pipe
 */
int						d_pipe_intro(int ac, char **av, char **path);

/*
 * builtin
 */
int						blt_intro();
void					run_echo(t_blt *blt, t_env *env);
void					run_cd(t_blt *blt, t_env *env, t_lst *envl);
void					run_env(int xprt_flag, t_lst *envl);
void					run_export(t_blt *blt, t_lst *envl);
void					run_pwd(t_lst *envl);
void					run_unset(char **all_env, t_blt *blt, t_env *env, t_lst *envl);

/*
 *search_env
 */
void					change_env_lst(char *bfore_key, char *after_key, t_lst *env);
t_env					*search_env_node(char *key, t_lst *env);
char					*search_env_value(char *key, t_lst *env);
t_env					*change_env_value(char *key, char *new_value, t_lst *env);

/*
 * heredoc
 */
int						hdoc_intro();
void					run_hdoc(t_hdoc *hdoc, t_syntax *stx);

#endif
