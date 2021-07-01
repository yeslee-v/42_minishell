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
# include <sys/types.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PROMPT_EXIT "\033[0;32mminishell\033[0;31m$\033[0m exit"
# define PROMPT "\033[0;32mminishell\033[0;31m$\033[0m "
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\03[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

typedef struct				s_token
{
	char					*token;
	char					type;
	struct s_token	*next;
	struct s_token	*prev;
}							t_token;

typedef struct				s_syntax
{
	int						i;
	char					*cmd;
	char					*option;
	char					*arg;
	struct s_syntax	*next;
	struct s_syntax	*prev;
}							t_syntax;

typedef struct				s_lst
{
	void					*head;
	void					*tail;
}							t_lst;

typedef struct				s_conf
{
	char					**env;
	char					*cmd;
	char					*lex;
	t_lst					*token;
	t_lst					*syntax;
	struct termios			term;
}							t_conf;

void						print_error(char *msg);

#endif
