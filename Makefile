#	INTRA_ID 	:	Input your intra ID.
#	INCS		:	Header files.
#	J_SRCS		:	Jaekpark's source files.
#	Y_SRCS		:	Yeslee's source files.
#	SRCS_DIR	:	Directory where source files are stored.
#	OBJS_DIR	:	Directory where object files will be stored.
#	INCS_DIR	:	Directory where header files are stored.
#	SRCS_FILE	:	Source files including directory path.
#	OBJS_FILE	:	Object files including directory path.
#	INCS_FILE	:	Header files including directory path.
#	
#	LIBFT		:	Own Library file name with path.
#	LIBFT_DIR	:	Directory where libft
#	LIBFT_INCS	:	Directory where libft's header file.
#
#	Cluster Readline
#	READLINE		=	 /Users/$(INTRA_ID)/.brew/opt/readline
# 	M1 mac Readline
# 	READLINE		=	/opt/homebrew/Cellar/readline/8.1

#	File settings
INTRA_ID			=	jaekpark
READLINE			=	/opt/homebrew/Cellar/readline/8.1
INCS				=	minishell.h
DIR_UTILS			=	0_utils/
DIR_SETUP			=	1_setup/
DIR_PARSE			=	2_parse/
DIR_EXEC			=	3_execute/
SRCS_UTILS			=	utils.c error/error.c error/exit_status.c \
						ft_utils/ft_double_strjoin.c ft_utils/ft_is.c ft_utils/ft_str_change.c \
						ft_utils/ft_strcjoin.c ft_utils/ft_strrdup.c ft_utils/ft_strstr.c \
						init/init_struct.c init/init_tool.c \
						free/free_lst.c free/free_struct.c \
						print/print.c print/print_utils.c print/print_node.c \
						struct/delete_env.c struct/make_struct.c struct/split_env.c 
SRCS_SETUP			=	signal/shell_signal.c signal/exec_signal.c \
						terminal/config.c terminal/cursor.c setup.c
SRCS_PARSE			=	redirection/heredoc.c redirection/redirect.c redirection/redirect_utils.c \
						analyze_command.c analyze_lexicon.c analyze_syntax.c analyze_token.c \
						analyze_utils.c lexer.c tokenizer.c parser.c parse_command.c parse_meta_char.c \
						parse_unclosed_pipe.c
SRCS_EXEC			=	builtin/blt_cd.c builtin/blt_echo.c builtin/blt_env.c builtin/blt_exit.c \
						builtin/blt_export.c builtin/blt_pwd.c builtin/blt_unset.c builtin/blt_utils.c \
						builtin/init_blt.c builtin/print_env.c \
						pipe/init_pipe.c pipe/run.c pipe/run_redir.c
SRCS				=	$(addprefix $(DIR_UTILS), $(SRCS_UTILS)) $(addprefix $(DIR_SETUP), $(SRCS_SETUP)) \
						$(addprefix $(DIR_PARSE), $(SRCS_PARSE)) $(addprefix $(DIR_EXEC), $(SRCS_EXEC)) main.c
OBJS				= 	$(patsubst %.c, %.o, $(SRCS_FILE))
SRCS_DIR			=	./srcs/
OBJS_DIR			=	./objs/
INCS_DIR			=	./includes/

SRCS_FILE			=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS_FILE			= 	$(addprefix $(OBJS_DIR), $(notdir $(OBJS)))
INCS_FILE			= 	$(addprefix $(INCS_DIR), $(INCS))

LIBFT				=	./libs/libft.a
LIBFT_DIR			=	./libs
LIBFT_INCS			=	./libs/includes/libft.h

#	Compile settings
CC					=	gcc
RM					=	rm -rf
CFLAGS				=	-Wall -Wextra -Werror -g -fsanitize=address
DFLAGS				= 	-Wall -Wextra -Werror -g -fsanitize=address
HEADER_FLAG			=	-I$(INCS_DIR) -I$(LIBFT_INCS) -I$(READLINE)/include
LIB_FLAG			= 	-L$(LIBFT_DIR) -lft -L$(READLINE)/lib -lreadline -lncurses
NAME				=	minishell
DEBUG				=	minishell_debug

#	Color settings
BLACK			=	"\033[1;30m"
RED				=	"\033[1;31m"
GREEN			=	"\033[1;32m"
YELLOW			=	"\033[1;33m"
BLUE			=	"\033[1;34m"
CYAN			=	"\033[1;35m"
PURPLE			=	"\033[1;36m"
WHITE			=	"\033[1;37m"
EOC				=	"\033[0;0m"

.c.o			:
					@clear
					@echo $(BLUE)
					$(CC) $(CFLAGS) $(HEADER_FLAG) -c $< -o $(addprefix $(OBJS_DIR), $(notdir $@))
					@echo $(EOC)

all				:	$(NAME)

debug			:	$(DEBUG)

$(LIBFT)		:
					@make -C ./libs

$(NAME)			:	$(LIBFT) $(OBJS_DIR) $(OBJS)
					@clear
					@echo $(GREEN)
					$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(OBJS_FILE) -o $@
					@echo $(EOC)
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: Compiling $@"
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

$(DEBUG)		:	$(LIBFT) $(OBJS_DIR) $(OBJS)
					@clear
					@echo $(PURPLE)
					$(CC) $(DFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(OBJS_FILE) -o $@
					@echo $(EOC)
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: Compiling $@"
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

$(OBJS_DIR)		:
					@mkdir -p $(OBJS_DIR)

norm			:	$(SRCS_FILE) $(INCS_FILE)
					@echo $(CYAN) "`date +%y/%m/%d_%H:%M:%S`:: minishell norm check"$(EOC)
					@norminette $(SRCS_FILE) $(INCS_FILE)
					@make norm -C $(LIBFT_DIR)

leaks			:
	 				@osascript -e 'tell app "Terminal" to do script "while true; do leaks minishell; sleep 2; clear; done"'

clean			:
					@make clean -C $(LIBFT_DIR)
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: clean minishell" $(EOC)
					@$(RM) $(OBJS_FILE) 
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

fclean			:
					@make fclean -C $(LIBFT_DIR)
					@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: fclean minishell" $(EOC)
					@$(RM) $(DEBUG) $(NAME) $(OBJS_DIR) 
					@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

re				:	fclean $(NAME)

.PHONY:			all clean fclean re norm leaks debug
