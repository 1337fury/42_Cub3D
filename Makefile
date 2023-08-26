#[abdeel-o]
NAME		= cub3D
CC 			= cc
FLAGS 		= -Wall -Wextra -Werror #-g -fsanitize=address
INC 		= -I include/cub3d -I include/MLX42 -I _libft/include -I _libft/libft -I gc_memory/include

GLFW		= -lglfw -L "/Users/abdeel-o/.brew/opt/glfw/lib"
MLX_F 		= -framework Cocoa -framework OpenGL -framework IOKit
MLX_LIB		= library/libmlx42.a
LIB_A       = library/libftprintf.a
GC_LIB		= library/gc_memory.a

#HOME SRCS LIST
HSL			= main.c _init.c
#PARSER SRCS LIST
PSL			= parser.c process_line.c
#UTILS SRCS LIST
USL			= checker.c errors.c helpers.c
#ENGINE SRCS LIST
ESL			= engine.c render.c render_utils.c textures.c input.c _3D_projection.c
#CASTER SRCS LIST
CSL 		= cast.c intersenctions.c init_part.c calculation.c

#PARSER SRCS PATH
PSP			= $(addprefix srcs/parser/,$(PSL))
#HOME SRCS PATH
HSP			= $(addprefix srcs/home/,$(HSL))
#UTILS SRCS PATH
USP			= $(addprefix srcs/utils/,$(USL))
#ENGINE SRCS PATH
ESP			= $(addprefix srcs/engine/,$(ESL))
#CASTER SRCS PATH
CSP 		= $(addprefix srcs/caster/,$(CSL))

#SOURCES LIST WITHOUT PATH
SL			= $(PSL) $(HSL) $(USL) $(ESL) $(CSL)

#SOURCES WITH PATH
SRCS		= $(PSP) $(HSP) $(USP) $(ESP) $(CSP)


#Object
O_DIR  		= object/
O_LIST      = $(patsubst %.c, %.o, $(SL))
OBJ         = $(addprefix $(O_DIR), $(O_LIST))


# COLORS
GREEN               = \033[0;32m
RED                 = \033[0;31m
RESET               = \033[0m

all: gc_comp libcomp $(NAME)

gc_comp :
	@make -C gc_memory/
	@cp gc_memory/gc_memory.a ./library

libcomp :
	@make -C _libft/
	@cp _libft/libftprintf.a ./library

$(NAME): $(O_DIR) $(OBJ)
	@tput el
	@$(CC) $(FLAGS) $(GLFW) $(OBJ) $(GC_LIB) $(MLX_LIB) $(LIB_A) -o $(NAME)
	@echo "$(RESET)\n$(NAME): $(GREEN)$(NAME) object files was created"
	@echo "$(RESET)$(NAME): $(GREEN)$(NAME) was created"

$(O_DIR):
	mkdir -p $(O_DIR)

$(O_DIR)%.o : srcs/parser/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

$(O_DIR)%.o : srcs/home/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

$(O_DIR)%.o : srcs/utils/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "Compiling $(GREEN)$@"

$(O_DIR)%.o : srcs/engine/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	echo "Compiling $(GREEN)$@"

$(O_DIR)%.o : srcs/caster/%.c
	@tput cuu1
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	echo "Compiling $(GREEN)$@"

clean:
	@rm -rf $(O_DIR)
	@make clean -C _libft/
	@make clean -C gc_memory/

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB_A)
	@rm -f $(GC_LIB)
	@make fclean -C _libft/

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re

#cc main.c libmlx42.a -Iinclude -lglfw -L "/Users/abdeel-o/.brew/opt/glfw/lib" -framework Cocoa -framework OpenGL -framework IOKit
