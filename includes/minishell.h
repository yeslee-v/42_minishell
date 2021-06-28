#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include "../libs/includes/libft.h"

# define MAXSIZE 1024
# define FALSE 0
# define TRUE 1
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define COLOR_BR_BLUE "\033[34;1m"
# define COLOR_WHITE "\033[37m"
# define COLOR_CYAN "\033[36m"
# define END_COLOR "\033[0m"
#endif
