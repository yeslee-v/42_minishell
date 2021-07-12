#Input Intra_ID
INTRA_ID			=	jaekpark
#Input header file name
INCS				=	minishell.h
#Input source files name
SRCS				=	main.c error.c ft_utils.c init.c make_struct.c free.c lexer.c tokenizer.c
OBJS				=	$(patsubst %.c, %.o, $(SRCS))

#Cluster Readline
#READLINE		=	 /Users/$(INTRA_ID)/.brew/opt/readline
READLINE		=	/opt/homebrew/Cellar/readline/8.1
SRCS_DIR		=	./srcs/
OBJS_DIR		=	./objs/
INCS_DIR		=	./includes/

SRCS_FILE		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJS_FILE		=	$(addprefix $(OBJS_DIR), $(OBJS))
INCS_FILE		= 	$(addprefix $(INCS_DIR), $(INCS))

LIBFT			=	./libs/libft.a
LIBFT_DIR		=	./libs
LIBFT_INCS		=	./libs/includes/libft.h

CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
HEADER_FLAG		=	-I$(INCS_DIR) -I$(LIBFT_INCS) -I$(READLINE)/include
LIB_FLAG		=	-lft -L$(LIBFT_DIR) -L$(READLINE)/lib -lreadline -lncurses
NAME			=	minishell

BLACK			=	"\033[1;30m"
RED				=	"\033[1;31m"
GREEN			=	"\033[1;32m"
YELLOW			=	"\033[1;33m"
BLUE			=	"\033[1;34m"
CYAN			=	"\033[1;35m"
PURPLE			=	"\033[1;36m"
WHITE			=	"\033[1;37m"
EOC				=	"\033[0;0m"

COMPILE			= 

all:			$(NAME)

$(LIBFT):
				@make -C ./libs

$(NAME):		$(LIBFT) $(OBJS_DIR) $(OBJS_FILE)
				@clear
				@echo $(GREEN)
				$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(OBJS_FILE) -o $@
				@echo $(EOC)
				@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: Compiling $@"
				@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

$(OBJS_DIR) :
					@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.c $(INCS_FILE)
					@clear
					@echo $(BLUE)
					$(CC) -c $(CFLAGS) $(HEADER_FLAG) $< -o $@
					@echo $(EOC)

norm:			$(SRCS_FILE) $(INCS_FILE)
				@echo $(CYAN) "`date +%y/%m/%d_%H:%M:%S`:: minishell norm check"$(EOC)
				@norminette $(SRCS_FILE) $(INCS_FILE)
				@make norm -C $(LIBFT_DIR)

leaks:
	 @osascript -e 'tell app "Terminal" to do script "while true; do leaks minishell; sleep 2; clear; done"'
# 	@osascript -e 'tell app "Terminal" to do script "while true; do leaks checker; sleep 2; clear; done"'
# 	@./utils/leaks.sh

clean:
				@make clean -C $(LIBFT_DIR)
				@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: clean minishell" $(EOC)
				@$(RM) $(OBJS_FILE) 
				@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

fclean:
				@make fclean -C $(LIBFT_DIR)
				@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: fclean minishell" $(EOC)
				@$(RM) $(NAME) $(OBJS_DIR) 
				@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

re:				fclean $(NAME) $(CLIENT)

.PHONY:			all clean fclean re norm
