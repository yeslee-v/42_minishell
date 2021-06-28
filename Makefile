NAME = pipe

HEADER = -I ./include

CC = gcc
CFLAGES = -Wall -Wextra -Werror

LIBFT = ./libs/libft
LIBFT_NAME = libft.a

RM = rm
RMFLAGS = -f

SRCS = ./srcs/pipe.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make all -C $(LIBFT)
	@cp $(LIBFT)/$(LIBFT_NAME) $(LIBFT_NAME)
	$(CC) $(CFLAGES) -L. -lft $(LFLAGES) $(LIBS) -o $@ $^

%.o:%.c
	@$(CC) $(CFLAGES) $(HEADER) -o $@ -c $<	

clean :
	$(RM) $(RMFLAGS) $(OBJS)
	 make clean -C $(LIBFT)

fclean : clean
	$(RM) $(RMFLAGS) $(NAME)
	$(RM) $(RMFLAGS) ./libft.a
	@make fclean -C $(LIBFT)

re : fclean all

.PHONY : all fclean clean re
