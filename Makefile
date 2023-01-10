CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror #-fsanitize=address
PS_H		= ./includes/
INCLUDE		= -I$(PS_H) -I$(MYLIBC_H)   
LDFLAGS		= -L$(MYLIBC_DIR)
MYLIBC 		= $(MYLIBC_DIR)mylibc.a
MYLIBC_DIR 	= ./mylibc/
MYLIBC_H 	= $(MYLIBC_DIR)

SRCS 		= ./src/hanoi_sort.c\
			./src/parse_input.c\
			./src/allowed_instructions.c\
			./src/sort_stack.c\
			./src/sort_stack2.c\
			
BONUS 		= ./src_checker/hanoi_sort_checker.c\
			./src_checker/parse_input_checker.c\
			./src_checker/allowed_instructions_checker.c\
		
OBJS 		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS:.c=.o)
NAME		= hanoi_sort
BONUS_N		= checker

all			: mylibc $(NAME)

$(NAME)		: $(OBJS) $(MYLIBC)
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LDFLAGS) $(MYLIBC) -o $(NAME)

checker		: mylibc $(BONUS_N)
	
$(BONUS_N)	: $(BONUS_OBJS)  $(MYLIBC)
			$(CC) $(CFLAGS) $(INCLUDE) $(BONUS_OBJS) $(LDFLAGS) $(MYLIBC) -o $(BONUS_N)

mylibc		:
			make -C $(MYLIBC_DIR)

clean		:
			make -C $(MYLIBC_DIR) clean
			rm -f $(OBJS) $(BONUS_OBJS)

fclean		: clean
			make -C $(MYLIBC_DIR) fclean
			rm -f $(NAME) $(BONUS_N)

re			: fclean all

rechecker		: fclean checker

.PHONY		: all clean fclean re checker mylibc