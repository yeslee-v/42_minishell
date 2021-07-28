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
int	set_heredoc(void);
void	set_input_redirect(void);
void	set_output_redirect(void);
int	set_redirect(void);
int	exec_heredoc(char *delimiter, int hdoc_fd);

/*
 *analyze_command
 */
void	analyze_cmd(void);
void	parse_cmd(t_process *node, t_lst *env);
void	get_redirect_file(t_lst *redir, t_cmd *tmp);
char	*make_bin_with_path(t_cmd *node, t_lst *env);
int	check_cmd_contain_path(t_cmd *node);
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
void	save_process(t_cmd *cmd, t_lst *redir, t_lst *hdoc);
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

/*
 *ft_utils
 */
char	*ft_strrdup(char *s, int st, int ed);
char	*ft_strcjoin(char *s1, char *s2, char c);
char	**split_env(char *env);

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
void	print_redir(t_process *proc, t_lst *redir);
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
void					intro(int cnt);
void					dup_close(int fd, int fd_std);
void					pipe_intro(int proc_cnt);

/*
 *single-pipe
 */
int		single_pipe(char **av, char **path);
void	print_error(char *str);
void	child_proc(char **av, char **path);
void	parents_proc(char **av, char **path);
void	split_path(char *cmd, char *path);
void	combine_cmd(char *cmd, char **path);
void	connect_in(char *file);
void	connect_out(char *file);
void	run_dup2(int std_fd, int *fd);
void	close_fd(int flag, int *fd);
void	run_execve();

/*
 * multi-pipe
 */
/*
 *int						multi_pipe(int cnt, char *path);
 *void					set_wait(void);
 *void					middle_proc(int cnt, char **av, char *path, t_all *all);
 *void					alloc_fd(int cnt, t_all *all);
 *void					ctrl_mid_cmd(int cnt, char *av, char *path, t_all *all);
 */

/*
 * builtin
 */
void	blt_intro(char *cmd, char *b_args);
int		is_blt(char *cmd);
void	not_blt(char *cmd, t_lst *envl);
void	run_echo(char *b_args, t_blt *blt);
void	run_cd(char *b_args, t_blt *blt, t_lst *envl);
void	run_env(int xprt_flag, t_lst *envl);
void	run_export(char *b_args, t_blt *blt, t_lst *envl);
void	run_pwd(t_lst *envl);
void	run_unset(char *b_args, t_blt *blt, t_lst *envl);

/*
 *search_env
 */
void	change_env_lst(char *bfore_key, char *after_key, t_lst *env);
t_env	*search_env_node(char *key, t_lst *env);
char	*search_env_value(char *key, t_lst *env);
t_env	*change_env_value(char *key, char *new_value, t_lst *env);

char	*unclosed_pipe(void);
char	**ft_double_strjoin(char **dst, char *src);

#endif
