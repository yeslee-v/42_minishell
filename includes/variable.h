#ifndef VARIABLE_H
# define VARIABLE_H

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

# define S_CMD 0
# define S_ARG 1
# define S_HDOC 2
# define S_AREDIR 3
# define S_IREDIR 4
# define S_OREDIR 5
# define S_FD 6

# define B_ECHO 1
# define B_ENV 2
# define B_PWD 3
# define B_EXPORT 4
# define B_UNSET 5
# define B_CD 6
# define B_EXIT 7

# define READ 0
# define WRITE 1

# define PROMPT "\033[1;32mBraveShell\033[0;31m$\033[0m "
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define B_RED "\033[1;31m"
# define GREEN "\033[0;32m"
# define B_GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define B_YELLOW "\033[1;33m"
# define BLUE "\033[0;34m"
# define B_BLUE "\033[1;34m"
# define PURPLE "\033[0;35m"
# define B_PURPLE "\033[1;35m"
# define CYAN "\033[0;36m"
# define B_CYAN "\033[1;36m"
# define WHITE "\033[0;37m"
# define B_WHITE "\033[1;30m"
# define RESET "\033[0m"

# define ERR_TOKEN "BraveShell: syntax error near unexpected token"
# define ERR_TOKEN_NL "BraveShell: syntax error near unexpected token `newline'"
# define ERR_TOKEN_EOF "BraveShell: syntax error: unexpected end of file\n"
# define ERR_QUOTE "BraveShell: syntax error: unexpected token `quote\""

# define BS "BraveShell"
# define CNF "command not found"
# define NFD "No such file or directory"
# define NVI "not a valid identifier"
# define ENF "event not found"

# define ERRNO_CMD_NOT_FOUND 127
# define ERRNO_SIGINT 130
# define ERRNO_SIGQUIT 131
# define ERRNO_UNEXPECTED_TOKEN 258

#endif
