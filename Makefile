#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Project Name
NAME			=	minirt

# Compiler Setting
CC				=	cc
CFLAG			=	-Wall -Wextra -Werror -g3

# Directory
INC_DIR			=	include/
LIB_DIR			=	lib/
OBJ_DIR			=	obj/
SRC_DIR			=	src/

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Source File
SRC				=	$(addprefix src/, \
					minirt.c \
					parser/ft_lst_to_arr.c \
					parser/ft_parser.c \
					parser/parse_mesh.c \
					parser/parse_unique.c \
					parser/parse_value_1.c \
					parser/parse_value_2.c \
					path_tracer/simple_tracer/st.c \
					path_tracer/restir_utils.c \
					$(UTILS) \
					)

UTILS			=	$(addprefix utils/, \
					ft_error.c \
					matrix.c \
					)

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Object File
OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Include Flag
IFLAG			=	$(addprefix -I, \
					$(INC_DIR) \
					$(LIBFT_DIR)/include \
					$(MLX42_DIR)/include/MLX42 \
					)

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Library Path & File
LIBFT_DIR		=	$(LIB_DIR)libft/
LIBFT			=	$(LIBFT_DIR)libft.a
MLX42_DIR		=	$(LIB_DIR)MLX42/
MLX42			=	$(MLX42_DIR)/build/libmlx42.a

# Library Dependencies for MLX42
MLX_DEPS		=	-ldl -lglfw -pthread -lm

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# All Target
all: $(NAME)

# LibFT Make Rule
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

# MLX42 Make Rule
$(MLX42):
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

# Main Target
$(NAME): $(OBJ) $(LIBFT) $(MLX42)
	@$(CC) $(CFLAG) $(OBJ) $(LIBFT) $(MLX42) $(MLX_DEPS) -o $(NAME)
	@echo "Welcome $@ ! 🤩🤙"

# Object File Compilation Rule
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) $(IFLAG) -c $< -o $@
	@echo "Good Morning $(notdir $@) ! 👋😇"

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Mandatory Target
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(MLX42_DIR)/build
	@echo "See You Soon $(OBJ_DIR) And Your Content... 🤧💔"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "Bye-Bye $(NAME) ! 🥺💋"

re: fclean all

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Phony Target
.PHONY: all clean fclean re
