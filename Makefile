#Input Intra_ID
INTRA_ID			=	jaekpark
#Input header file name
INCS				=	minishell.h
#Input source files name
Y_SRCS				=	utils/error.c utils/ft_utils.c utils/init.c utils/make_struct.c utils/free.c parse/lexer.c parse/tokenizer.c 
J_SRCS				=	main.c
SRCS				=	$(Y_SRCS) $(J_SRCS)
OBJS				=	$(SRCS:.c=.o)
SRCS_SUB_DIR		=	$(addprefix $(OBJS_DIR), $(dir $(SRCS)))

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


all:			$(NAME)

$(LIBFT):
				@make -C ./libs

$(NAME):		$(LIBFT) $(OBJS_DIR) $(OBJS_FILE) $(OBJS)
				@clear
				@echo $(GREEN)
				$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(OBJS) -o $@
				@echo $(EOC)
				@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: Compiling $@"
				@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

$(OBJS_DIR) :
					@mkdir -p $(OBJS_DIR)
					@mkdir -p $(SRCS_SUB_DIR)

.c.o :	$(INCS_FILE)
					@clear
					@echo $(BLUE)
					$(CC) -c $(CFLAGS) $(HEADER_FLAG) $<
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
