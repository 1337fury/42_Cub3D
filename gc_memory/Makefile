NAME := gc_memory.a

FLAGS := -Wall -Wextra -Werror
SRCS  := src/
INC   := include
FILES := $(addprefix $(SRCS), gc_memory.c)
OBJS  := $(FILES:.c=.o)

all : $(NAME)
		@echo "[gc_memory ✅]"

$(NAME)	 : $(OBJS)
			@ar -rc $@ $^

.c.o	 : 
			@cc $(FLAGS) -c $< -o $@ -I $(INC)

clean 	: $(NAME)
			@echo "[clean ✅]"
			@rm -rf $(OBJS) $<

re 		: clean all