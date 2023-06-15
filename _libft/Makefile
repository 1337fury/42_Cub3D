#[abdeel-o]
NAME 		= libftprintf.a
CC 			= cc
CFLAFGS 	= -Wall -Wextra -Werror
LIB 		= ./libft/libft.a
INC 		= -I include

SOURCES_PATH = srcs
SOURCES_LIST = \
	ft_printf.c \
	ft_putstr.c \
	ft_putchar.c \
	ft_pformat.c \
	ft_putnbr.c \
	ft_putunsigned.c \
	ft_put_hexa.c \
	ft_putsign.c \
	ft_putptr.c \
	get_next_line.c \
	get_next_line_utils.c 
SOURCES 	= $(addprefix $(SRCS_PATH)/,$(SRCS_NAME))

OBJECTS_DIRECTORY   = object/
OBJECTS_LIST        = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS             = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

all : libftcomp $(NAME)

libftcomp :
	@make all -C ./libft

$(NAME) : $(OBJECTS_DIRECTORY) $(OBJECTS)
	@libtool -static -o $@ $(LIB) $(OBJECTS)

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o : srcs/%.c
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

clean :
	@make clean -C ./libft
	@rm -rf $(OBJECTS_DIRECTORY)

fclean : clean
	@make fclean -C ./libft
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
