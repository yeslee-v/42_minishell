#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/includes/libft.h"
# include "./struct.h"
# include "./variable.h"
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

/*
 * - lexer
 *	analyze_space
 *	analyze_quote
 *	analyze_operator
 */
t_lexer	*lexer(char *cmd);

/*
 * - token
 *   analyze_type
 *   set_index
 */
int		tokenizer(char *lex);
void	analyze_token(t_lst *token);
int		analyze_syntax(t_lst *token);
char	*unclosed_pipe(void);

/*
 * - parser
 *   parse syntax
 *   parse redir
 *   parse process
 */
t_token	*parser(t_token *tok);

/*
 *redirect
 */
int	set_heredoc(t_process *pipe);
int	set_input_redir_node(t_redirect *input);
int	set_output_redir_node(t_redirect *out);
int	print_redir_error(char *file, char *err_msg);
int	set_redirect(t_lst *process);
int	exec_heredoc(char *delimiter, int hdoc_fd);
int	set_all_redir_lst(t_process *pipe);
void	close_redir_fd(t_redirect *redir);
char *make_hdoc_file_name(int i);

int	redir_init(t_cmd *proc);

/*
 *analyze_command
 */
void	analyze_cmd(void);
void	parse_cmd(t_process *node, t_lst *env);
void	get_redirect_file(t_lst *redir, t_cmd *tmp);
char	*make_bin_with_path(t_cmd *node, t_lst *env);
int		check_cmd_contain_path(t_cmd *node);
char	**split_env_value(char *key, char c, t_lst *env);
void	make_cmd_with_path(t_cmd *node, char **path);
char	*find_bin(char **path);


/*
 *terminal
 */
int		get_cursor_pos(int *x, int *y);
void	set_terminal(void);
void	set_term_cursor(void);
int		set_term_default(int status);

/*
 *signal
 */
void	move_cursor(char *msg, int col, int row);
int		print_tc(int tc);
void	sig_handler(int signum);
void	set_signal(void);

/*
 *make_struct
 */
void	save_process(t_cmd *cmd, t_control *con);
void	make_token(t_lst *lst, int st, int ed);
void	make_env(t_lst *lst, char *key, char *value);
void	make_redir(t_lst *redir, char type, char *arg);

/*
 *cursor
 */
char	**split_arg(char *arg);

/*
 *init
 */
void	init_lst(t_lst *lst);
void	init_lexer(t_lexer *lexer);
void	init_tool(t_tool *tool);
void	init_config(void);
void	init_cmd(t_cmd *node);
void	init_control(t_control *con);
void	init_status(t_status *node);

/*
 *ft_utils
 */
char	*ft_strrdup(char *s, int st, int ed);
char	*ft_strcjoin(char *s1, char *s2, char c);
char	**split_env(char *env);
char	*ft_str_change(char *str, char *target, char *src);

/*
 *ft_is
 */
int		ft_isspace(int c);
int		ft_isquote(char c);
int		ft_isspec(char *cmd, int i);

/*
 *free_list
 */
void	free_env(t_lst *env);
void	free_syntax(t_lst *syntax);
void	free_process(t_lst *process);
void	free_token(t_lst *token);

/*
 *free_struct
 */
void	free_env_node(t_env *env);
void	free_conf(t_conf *conf);
void	free_lexer(t_lexer *lexer);
void	free_cmd(t_cmd *node);

/*
 *print_utils
 */
void	print_syntax(t_lst *syntax);
void	print_process(t_lst *process);
void	print_env(t_lst *env);
void	print_error(char *msg);
void	print_token(t_lst *token);
void	print_system(void);
void	print_double_str(char **str);
void	print_redir(t_control *con, t_lst *redir);
void	print_control(t_control *con);
void	print_cmd(t_cmd *node);

/*
 *set
 */
void	set_env(char **envp);
void	set_prompt(void);
void	set_process(void);

/*
 *exit
 */
void	exit_shell(int num);

/*
 *utils
 */
int		get_redir_fd(char *cmd);
void	delete_env_node(char *key, t_lst *env);
int		get_process_count(void);

/*
 *pipe
 */
void	pipe_intro(int cnt);
void	dup_close(int fd, int fd_std);
void	print_error(char *str);
void	run_execve(t_cmd *proc);

/*
 * builtin
 */
int		blt_intro(t_process *proc_lst);
void	init_blt(t_blt *blt);
void	set_lower(char *cmd, t_blt *blt);
int		is_blt(char *cmd);
void	run_builtin(t_cmd *proc, t_blt *blt);
void	not_blt(t_cmd *proc);
void	run_echo(char *b_args, t_blt *blt);
void	run_cd(char *b_args, t_blt *blt);
void	run_env(int xprt_flag);
void	run_export(char *b_args, t_blt *blt);
void	run_pwd(void);
void	run_unset(char *b_args, t_blt *blt);

/*
 *search_env
 */
void	change_env_lst(char *bfore_key, char *after_key, t_lst *env);
t_env	*search_env_node(char *key, t_lst *env);
char	*search_env_value(char *key, t_lst *env);
t_env	*change_env_value(char *key, char *new_value, t_lst *env);

char	*unclosed_pipe(void);
char	**ft_double_strjoin(char **dst, char *src);

/*
 *exit_status
 */
void	print_status(int num, t_cmd *proc);

#endif
