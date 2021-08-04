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
 *- 0_utils
 */
void	remove_hdoc(int i);
int		get_process_count(void);
/*
 *- 0_utils/error
 */
void	error_with_message(char *msg, int exit_status);
void	print_status(int num, t_cmd *proc);
void	token_error(char *token, int exit_status);
int		redir_error(char *file, char *err_msg);
void	cd_error(char *dir, char *err_msg);
/*
 *- 0_utils/free
 */
void	free_env(t_lst *env);
void	free_redirect(t_lst *redir);
void	free_token(t_lst *token);
void	free_control(t_control *con);
void	free_process(t_lst *process);
void	free_conf(t_conf *conf);
void	free_lexer(t_lexer *lexer);
void	free_cmd(t_cmd *node);
void	free_env_node(t_env *env);
/*
 *- 0_utils/ft_utils
 */
char	**ft_double_strjoin(char **dst, char *src);
int		ft_isspec(char *cmd, int i);
int		ft_isspace(int c);
int		ft_isquote(char c);
char	*ft_str_change(char *str, char *src, int st, int ed);
char	*ft_strcjoin(char *s1, char *s2, char c);
char	*ft_strrdup(char *s, int st, int ed);
char	*ft_strstr(char *str, char *src);
/*
 *- 0_utils/init
 */
void	init_cmd(t_cmd *node);
void	init_config(void);
void	init_lexer(t_lexer *lexer);
void	init_lst(t_lst *lst);
void	init_control(t_control *con);
void	init_tool(t_tool *tool);
/*
 *- 0_utils/print
 */
void	print_token(t_lst *token);
void	print_env(t_lst *env);
void	print_cmd(t_cmd *node);
void	print_redir(t_control *con, t_lst *redir);
void	print_control(t_control *con);
void	print_process(t_lst *process);
void	print_double_str(char **str);
void	print_system(void);
/*
 *- 0_utils/struct
 */
void	delete_env_node(char *key, t_lst *env);
void	save_process(t_cmd *cmd, t_control *con);
void	make_token(t_lst *lst, int st, int ed);
void	make_env(t_lst *lst, char *key, char *value);
void	make_redir(t_lst *redir, char type, char *arg);
char	**split_env(char *env);
/*
 *- 1_setup
 */
void	set_prompt(void);
int		set_process(void);
void	set_env(char **envp);
int		set_cmd_after_pipe(void);
/*
 *- 1_setup/signal
 */
void	sigint_handler(int signum);
void	set_signal(void);
void	hdoc_sig_handler(int signum);
void	exec_sigint(int signum);
void	exec_sigquit(int signum);
/*
 *- 1_setup/terminal
 */
void	set_term_cursor(void);
int		set_term_default(int status);
void	set_terminal(void);
void	return_terminal(void);
int		get_cursor_pos(int *x, int *y);
void	move_cursor(char *msg, int col, int row);
/*
 *- 2_parse
 */
t_lexer	*lexer(char *cmd);
int		tokenizer(char *lex);
t_token	*parser(t_token *token);
void	seperate_redir(t_control *con, char type, char *token);
t_token	*parse_token(t_token *tok, t_cmd *node, t_control *con);

void	get_redirect_file(t_lst *redir, t_cmd *tmp);
void	parse_command(t_process *node, t_lst *env);
void	remove_arg_quote(char **arg);
void	remove_cmd_quote(t_cmd *node);
void	analyze_command(void);
int		calc_echo(t_cmd *proc, t_blt *blt);

void	analyze_space(t_lexer *lexer, int i);
void	analyze_quote_pair(t_lexer *lexer, char c, int i);
void	analyze_operator(char *lex, int ret, int *i);
void	check_in_quote(t_lexer *lexer, int i);
void	analyze_lexicon(t_lexer *lexer, char *cmd, int *i);

void	mark_token_type(t_token *tmp, char type, int *find_cmd);
int		check_unexpected_token(t_token *node);
int		check_token_type(t_lst *token, t_token *tmp, int find);
int		analyze_unexpected_token(t_token *tok);
int		analyze_syntax(t_lst *token);
void	analyze_token(t_lst *token);
int		check_valid_char(char c);
char	*get_env_in_cmd(char *str, char *lex);
int		get_arg_cnt(char *lex);
char	*strdup_only_char(char *lex, char *str);
int		check_quote_exist(char *lex);

char	*find_bin(char **path);
void	make_cmd_with_path(t_cmd *node, char **path);
char	**split_env_value(char *key, char c, t_lst *env);
int		check_cmd_contain_path(t_cmd *node);
char	*make_bin_with_path(t_cmd *node, t_lst *env);
void	set_meta_character(t_lst *token);
char	*unclosed_pipe(void);
/*
 *- 2_parse/redirection
 */
int		exec_heredoc(char *delimeter, int hdoc_fd);
int		set_output_redir_node(t_redirect *out);
int		set_input_redir_node(t_redirect *input);
int		set_heredoc(t_process *pipe);
int		set_all_redir_lst(t_process *pipe);
int		set_redirect(t_lst *process);
int		exit_hdoc(char **file, int ret);
char	*make_hdoc_file_name(int i);
void	close_redir_fd(t_redirect *redir);
/*
 *- 3_execute/builtin
 */
int		is_chdir(int ret, char *abs_pwd);
void	relative_path(char **b_args, char buf[512]);
void	run_cd(char *b_args, t_blt *blt);
int		exists_opt(int i, char **tmp);
void	is_env(char *tmp);
void	do_echo(int i, char **tmp, t_blt *blt);
int		is_up_flag(char **tmp, t_blt *blt);
void	run_echo(t_cmd *proc, t_blt *blt);
void	run_env(int xprt_flag);
void	run_exit(char **args);
void	run_export(t_cmd *proc, t_blt *blt);
void	run_pwd(void);
//void	run_unset(char **args, t_blt *blt);
void	run_unset(char *b_args, t_cmd *proc, t_blt *blt);
int		check_args(char *b_args, t_cmd *proc);
void	init_blt(t_blt *blt);
void	set_lower(char *cmd, t_blt *blt);
int		is_blt(char *cmd);
void	run_builtin(int num, t_cmd *proc, t_blt *blt);
void	not_blt(t_cmd *proc);
int		blt_intro(t_process *proc_lst);
t_env	*search_env_node(char *key, t_lst *env);
char	*search_env_value(char *key, t_lst *env);
t_env	*change_env_value(char *key, char *new_value, t_lst *env);
void	change_env_lst(char *bfore_key, char *after_key, t_lst *envl);
/*
 *- 3_execute/pipe
 */
void	run_in_child(int i, int cnt, int *fd_prev, t_process *proc_lst);
void	run_in_parents(int i, int cnt, int *fd_prev, t_cmd *proc);
int		redir_in_pipe(t_process *proc_lst);
void	run_pipe(int cnt);
int		double_strlen(const char **str);
void	run_execve(t_cmd *proc);
void	pipe_intro(int cnt);
void	dup_close(int fd, int fd_std);
int		in_redir(t_cmd *proc);
void	out_redir(t_cmd *proc);
void	append_redir(t_cmd *proc);
int		redir_init(t_cmd *proc);
#endif
