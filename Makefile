<<<<<<< HEAD
<<<<<<< HEAD
NAME = pipe

HEADER = -I ./includes

CC = gcc
CFLAGES = -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT = ./libs/libft
LIBFT_NAME = libft.a

RM = rm
RMFLAGS = -f

# SRCS = ./srcs/pipe/pipe.c \
#	   ./srcs/print_error.c \
#	   ./srcs/pipe/set_cmd.c \
#	   ./srcs/pipe/redirect.c \
#	   ./srcs/pipe/run.c \

SRCS = ./srcs/builtin/blt_echo.c \
	   ./srcs/builtin/blt_cd.c \
	   ./srcs/builtin/blt_pwd.c \
	   ./srcs/builtin/blt_export.c \
	   ./srcs/builtin/blt_unset.c \
	   ./srcs/builtin/blt_env.c \
	   ./srcs/builtin/blt_exit.c

#SRCS = ./srcs/heredoc.c \
	   #./libs/get_next_line.c \
	   #./libs/get_next_line.h \
	   #./libs/get_next_line_utils.c \
	   #./srcs/print_error.c \
	   #./srcs/set_cmd.c \
	   #./srcs/redirect.c \
	   #./srcs/run.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make all -C $(LIBFT)
	@cp $(LIBFT)/$(LIBFT_NAME) $(LIBFT_NAME)
	@$(CC) $(CFLAGES) -L. -lft $(LFLAGES) $(LIBS) -o $@ $^

%.o:%.c
	@$(CC) $(CFLAGES) $(HEADER) -o $@ -c $<	

clean :
	@$(RM) $(RMFLAGS) $(OBJS)
	@make clean -C $(LIBFT)

fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)
	@$(RM) $(RMFLAGS) ./libft.a
	@make fclean -C $(LIBFT)

re : fclean all

.PHONY : all fclean clean re
=======
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
=======
#Input header file name
INCS				=	minishell.h
#Input source files name
SRCS				=	main.c
OBJS				=	$(patsubst %.c, %.o, $(SRCS))

>>>>>>> main
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
<<<<<<< HEAD
HEADER_FLAG		=	-I$(INCS_DIR) -I$(LIBFT_INCS) -I$(READLINE)/include
LIB_FLAG		=	-lft -L$(LIBFT_DIR) -L$(READLINE)/lib -lreadline -lncurses
=======
HEADER_FLAG		=	-I$(INCS_DIR) -I$(LIBFT_INCS)
LIB_FLAG		=	-lft -L$(LIBFT_DIR) -L/usr/include -lreadline
>>>>>>> main
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

<<<<<<< HEAD
COMPILE			= 
=======
>>>>>>> main

all:			$(NAME)

$(LIBFT):
<<<<<<< HEAD
				@make -C ./libs

$(NAME):		$(LIBFT) $(OBJS_DIR) $(OBJS_FILE)
				@clear
				@echo $(GREEN)
				$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(OBJS_FILE) -o $@
				@echo $(EOC)
				@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: Compiling $@"
				@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)
=======
				@make -C ./libft

$(NAME):		$(LIBFT) $(OBJS_DIR) $(OBJS_FILE)
				@echo $(YELLOW) " - Compiling $@"
				@$(CC) $(CFLAGS) $(LIB_FLAG) $(HEADER_FLAG) $(OBJS_FILE) -o $@
				@echo $(GREEN) " - OK" $(EOC)
>>>>>>> main

$(OBJS_DIR) :
					@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o :	$(SRCS_DIR)%.c $(INCS_FILE)
<<<<<<< HEAD
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
=======
					@$(CC) -c $(CFLAGS) $(HEADER_FLAG) $< -o $@

norm:			$(SRCS_FILE) $(INCS_FILE)
				@echo $(CYAN) " - minishell norm check"$(EOC)
				@norminette $(SRCS_FILE) $(INCS_FILE)
				@make norm -C $(LIBFT_DIR)

# leaks:
# 	@osascript -e 'tell app "Terminal" to do script "while true; do leaks push_swap; sleep 2; clear; done"'
>>>>>>> main
# 	@osascript -e 'tell app "Terminal" to do script "while true; do leaks checker; sleep 2; clear; done"'
# 	@./utils/leaks.sh

clean:
				@make clean -C $(LIBFT_DIR)
<<<<<<< HEAD
				@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: clean minishell" $(EOC)
				@$(RM) $(OBJS_FILE) 
				@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)

fclean:
				@make fclean -C $(LIBFT_DIR)
				@echo $(YELLOW) "`date +%y/%m/%d_%H:%M:%S`:: fclean minishell" $(EOC)
				@$(RM) $(NAME) $(OBJS_DIR) 
				@echo $(GREEN) "`date +%y/%m/%d_%H:%M:%S`:: OK" $(EOC)
=======
				@echo $(YELLOW) " - clean push_swap" $(EOC)
				@$(RM) $(OBJS_FILE) 
				@echo $(GREEN) " - OK" $(EOC)

fclean:
				@make fclean -C $(LIBFT_DIR)
				@echo $(YELLOW) " - fclean minitalk" $(EOC)
				@$(RM) $(NAME) $(OBJS_DIR) 
				@echo $(GREEN) " - OK" $(EOC)
>>>>>>> main

re:				fclean $(NAME) $(CLIENT)

.PHONY:			all clean fclean re norm
<<<<<<< HEAD
>>>>>>> jaekpark
=======
>>>>>>> main
